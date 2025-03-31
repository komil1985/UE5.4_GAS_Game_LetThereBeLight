// Copyright ASKD Games


#include "AbilitySystem/ExecCal/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/KDAttributeSet.h"
#include <Misc/KDGameplayTags.h>
#include <AbilitySystem/Data/CharacterClassInfo.h>
#include <AbilitySystem/KDAbilitySystemLibrary.h>
#include <Interactions/CombatInterface.h>
#include <KDAbilityTypes.h>
#include "Kismet/GameplayStatics.h"


struct KDDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);

	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(IceResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);

	KDDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKDAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKDAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKDAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKDAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKDAttributeSet, CriticalHitResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKDAttributeSet, CriticalHitDamage, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UKDAttributeSet, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKDAttributeSet, IceResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKDAttributeSet, LightningResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKDAttributeSet, PhysicalResistance, Target, false);

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
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);

	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().IceResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
}


void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	const FKDGameplayTags& Tags = FKDGameplayTags::Get();
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Armor, DamageStatics().ArmorDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_ArmorPenetration, DamageStatics().ArmorPenetrationDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_BlockChance, DamageStatics().BlockChanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitChance, DamageStatics().CriticalHitChanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitResistance, DamageStatics().CriticalHitResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitDamage, DamageStatics().CriticalHitDamageDef);

	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Fire, DamageStatics().FireResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Ice, DamageStatics().IceResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Lightning, DamageStatics().LightningResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Physical, DamageStatics().PhysicalResistanceDef);


	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	int32 SourcePlayerLevel = 1;
	if (SourceAvatar && SourceAvatar->Implements<UCombatInterface>())
	{
		SourcePlayerLevel = ICombatInterface::Execute_GetPlayerLevel(SourceAvatar);
	}
	int32 TargetPlayerLevel = 1;
	if (TargetAvatar && TargetAvatar->Implements<UCombatInterface>())
	{
		TargetPlayerLevel = ICombatInterface::Execute_GetPlayerLevel(TargetAvatar);
	}


	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags;
	EvaluationParameters.TargetTags;

	// Debuffs
	const FKDGameplayTags& GameplayTags = FKDGameplayTags::Get();
	for (const TTuple<FGameplayTag, FGameplayTag>& Pair : GameplayTags.DamageTypesToDebuffs)
	{
		const FGameplayTag& DamageType = Pair.Key;
		const FGameplayTag& DebuffType = Pair.Value;
		const float TypeDamage = Spec.GetSetByCallerMagnitude(DamageType, false, -1.0f);
		if (TypeDamage > -0.5f) // .5 padding for floating point [im]precision
		{
			// Determine if there was a successful debuff
			const float SourceDebuffChance = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Chance, false, -1.0f);

			float TargetDebuffResistance = 0.0f;
			
			const FGameplayTag& ResistanceTag = GameplayTags.DamageTypesToResistances[DamageType];
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(TagsToCaptureDefs[ResistanceTag], EvaluationParameters, TargetDebuffResistance);
			TargetDebuffResistance = FMath::Max<float>(TargetDebuffResistance, 0.0f);
			const float EffectiveDebuffChance = SourceDebuffChance * (100 - TargetDebuffResistance) / 100.0f;
			const bool bDebuff = FMath::RandRange(1, 100) < EffectiveDebuffChance;
			if (bDebuff)
			{
				FGameplayEffectContextHandle ContextHandle = Spec.GetContext();

				UKDAbilitySystemLibrary::SetIsSuccessfulDebuff(ContextHandle, true);
				UKDAbilitySystemLibrary::SetDamageType(ContextHandle, DamageType);

				const float DebuffDamage = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Damage, false, -1.0f);
				const float DebuffDuration = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Duration, false, -1.0f);
				const float DebuffFrequency = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Frequency, false, -1.0f);

				UKDAbilitySystemLibrary::SetDebuffDamage(ContextHandle, DebuffDamage);
				UKDAbilitySystemLibrary::SetDebuffDuration(ContextHandle, DebuffDuration);
				UKDAbilitySystemLibrary::SetDebuffFrequency(ContextHandle, DebuffFrequency);
			}
		}
	}


	// Get Damage Set By Caller Magnitude
	float Damage = 0.0f;
	for (const TTuple<FGameplayTag, FGameplayTag>& Pair : FKDGameplayTags::Get().DamageTypesToResistances)
	{
		const FGameplayTag DamageTypeTag = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;

		checkf(TagsToCaptureDefs.Contains(ResistanceTag), TEXT("TagsToCaptureDefs doesn't contain Tag: [%s] in ExecCalc_Damage"), *ResistanceTag.ToString());
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = TagsToCaptureDefs[ResistanceTag];

		float DamageTypesValue = Spec.GetSetByCallerMagnitude(Pair.Key, false, 0.0f);

		float Resistance = 0.0f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluationParameters, Resistance);
		Resistance = FMath::Clamp(Resistance, 0.0f, 100.0f);

		DamageTypesValue *= (100.0f - Resistance) / 100.0f;

		if (UKDAbilitySystemLibrary::IsRadialDamage(EffectContextHandle))
		{
			if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(TargetAvatar))
			{
				CombatInterface->GetOnDamageDelegate().AddLambda
				(
					[&](float DamageAmount)
					{
						DamageTypesValue = DamageAmount;
					}
				);
			}
			UGameplayStatics::ApplyRadialDamageWithFalloff
			(
				TargetAvatar,
				DamageTypesValue,
				0.0f,
				UKDAbilitySystemLibrary::GetRadialDamageOrigin(EffectContextHandle),
				UKDAbilitySystemLibrary::GetRadialDamageInnerRadius(EffectContextHandle),
				UKDAbilitySystemLibrary::GetRadialDamageOuterRadius(EffectContextHandle),
				1.0f,
				UDamageType::StaticClass(),
				TArray<AActor*>(),
				SourceAvatar,
				nullptr
			);
		}

		Damage += DamageTypesValue;
	}

	// Capture BlockChance On Target, And Determine If There Was A Successful Block
	float TargetBlockChance = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude
	(
		DamageStatics().BlockChanceDef, 
		EvaluationParameters, 
		TargetBlockChance
	);
	TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.0f);
	
	const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;

	UKDAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);


	// If Block, Halve The Damage
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

	// Capture Source CriticalHitChance
	float SourceCriticalHitChance = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude
	(
		DamageStatics().CriticalHitChanceDef,
		EvaluationParameters,
		SourceCriticalHitChance
	);
	SourceCriticalHitChance = FMath::Max<float>(SourceCriticalHitChance, 0.0f);

	// Capture Target CriticalHitResistance
	float TargetCriticalHitResistance = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude
	(
		DamageStatics().CriticalHitResistanceDef,
		EvaluationParameters,
		TargetCriticalHitResistance
	);
	TargetCriticalHitResistance = FMath::Max<float>(TargetCriticalHitResistance, 0.0f);

	// Capture Source CriticalHitDamage
	float SourceCriticalHitDamage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude
	(
		DamageStatics().CriticalHitDamageDef,
		EvaluationParameters,
		SourceCriticalHitDamage
	);
	SourceCriticalHitDamage = FMath::Max<float>(SourceCriticalHitDamage, 0.0f);

	const UCharacterClassInfo* CharacterClassInfo = UKDAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);
	
	// ArmorPenetration Coefficient
	const FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString());
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourcePlayerLevel);
	// ArmorPenetration ignores a percentage of the Target's Armor.
	const float EffectiveArmor = TargetArmor * (100 - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100.0f;

	// EffectiveArmor Coefficient
	const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetPlayerLevel);
	// Armor ignores a precentage of incoming Damage.
	Damage *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100.0f;

	// CriticalHitResistance Curve & Coefficient
	const FRealCurve* CriticalHitResistanceCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("CriticalHitResistance"), FString());
	const float CriticalHitResistanceCoefficient = CriticalHitResistanceCurve->Eval(TargetPlayerLevel);

	// CriticalHit Resistance reduces CriticalHitChance by a certain percentage
	const float EffectiveCriticalHitChance = SourceCriticalHitChance - TargetCriticalHitResistance * CriticalHitResistanceCoefficient;
	const bool bCriticalHit = FMath::RandRange(1, 100) < EffectiveCriticalHitChance;

	UKDAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCriticalHit);

	// Double Damage plus a bonus if its a critical hit
	Damage = bCriticalHit ? 2.0f * Damage + SourceCriticalHitDamage : Damage;

	const FGameplayModifierEvaluatedData EvaluatedData(UKDAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
