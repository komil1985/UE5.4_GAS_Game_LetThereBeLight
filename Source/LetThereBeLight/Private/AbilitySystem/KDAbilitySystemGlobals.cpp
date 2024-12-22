// Copyright ASKD Games


#include "AbilitySystem/KDAbilitySystemGlobals.h"
#include "KDAbilityTypes.h"

FGameplayEffectContext* UKDAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FKDGameplayEffectContext();
}
