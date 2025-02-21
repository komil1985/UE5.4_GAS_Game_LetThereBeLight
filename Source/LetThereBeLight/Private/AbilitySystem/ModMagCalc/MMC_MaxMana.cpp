// Copyright ASKD Games


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"
#include "AbilitySystem/KDAttributeSet.h"
#include "Interactions/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDefinition.AttributeToCapture = UKDAttributeSet::GetIntelligenceAttribute();
	IntelligenceDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDefinition.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDefinition);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// 	Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Intelligence = 0.0f;
	GetCapturedAttributeMagnitude(IntelligenceDefinition, Spec, EvaluationParameters, Intelligence);
	Intelligence = FMath::Max<float>(Intelligence, 0.0f);

	int32 PlayerLevel = 1;
	if (Spec.GetContext().GetSourceObject()->Implements<UCombatInterface>())
	{
		PlayerLevel = ICombatInterface::Execute_GetPlayerLevel(Spec.GetContext().GetSourceObject());
	}

	float BaseValue = 50.0f;
	float Magnitude = 5.0f;
	float ExtraValue = 10.0f;

	return BaseValue + (Magnitude * Intelligence) + (ExtraValue * PlayerLevel);
}
