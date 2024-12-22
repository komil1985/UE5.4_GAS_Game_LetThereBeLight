// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "KDAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API UKDAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
