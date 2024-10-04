// Copyright ASKD Games


#include "AbilitySystem/KDAbilitySystemComponent.h"

void UKDAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UKDAbilitySystemComponent::EffectApplied);
}

void UKDAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	GEngine->AddOnScreenDebugMessage(1, 8.0f, FColor::Blue, FString("Effect Applied"));
}
