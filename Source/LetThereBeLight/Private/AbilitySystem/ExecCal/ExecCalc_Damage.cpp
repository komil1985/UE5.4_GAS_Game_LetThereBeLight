// Copyright ASKD Games


#include "AbilitySystem/ExecCal/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/KDAttributeSet.h"
#include <Misc/KDGameplayTags.h>
#include <AbilitySystem/Data/CharacterClassInfo.h>
#include <AbilitySystem/KDAbilitySystemLibrary.h>
#include <Interactions/CombatInterface.h>


struct KDDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);

	KDDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKDAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKDAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKDAttributeSet, BlockChance, Target, false);

	}
};

static const KDDamageStatics& DamageStatics()
{
	static KDDamageStatics DStatics;
	return DStatics;
}


UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);

}


void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	ICombatInterface* TargetCombatinterface = Cast<ICombatInterface>(TargetAvatar);

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags;
	EvaluationParameters.TargetTags;

	// Get Damage Set By Caller Magnitude
	float Damage = Spec.GetSetByCallerMagnitude(FKDGameplayTags::Get().Damage);

	// Capture BlockChance On Target, And Determine If There Was A Successful Block
	float TargetBlockChance = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude
	(
		DamageStatics().BlockChanceDef, 
		EvaluationParameters, 
		TargetBlockChance
	);
	TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.0f);
	
	// If Block, Halve The Damage
	const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;
	if (bBlocked) { Damage = Damage / 2.0f; }

	// Capture Target Armor
	float TargetArmor = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude
	(
		DamageStatics().ArmorDef, 
		EvaluationParameters, 
		TargetArmor
	);
	TargetArmor = FMath::Max<float>(TargetArmor, 0.0f);

	// Capture Source ArmorPenetration
	float SourceArmorPenetration = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude
	(
		DamageStatics().ArmorPenetrationDef, 
		EvaluationParameters, 
		SourceArmorPenetration
	);
	SourceArmorPenetration = FMath::Max<float>(SourceArmorPenetration, 0.0f);

	const UCharacterClassInfo* CharacterClassInfo = UKDAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);
	
	const FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString());
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourceCombatInterface->GetPlayerLevel());
	// ArmorPenetration ignores a percentage of the Target's Armor.
	const float EffectiveArmor = TargetArmor * (100 - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100.0f;

	const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetCombatinterface->GetPlayerLevel());
	// Armor ignores a precentage of incoming Damage.
	Damage *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100.0f;

	const FGameplayModifierEvaluatedData EvaluatedData(UKDAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
