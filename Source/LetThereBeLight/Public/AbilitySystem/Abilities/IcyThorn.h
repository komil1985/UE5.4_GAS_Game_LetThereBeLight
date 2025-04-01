// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/KDDamageGameplayAbility.h"
#include "IcyThorn.generated.h"

/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API UIcyThorn : public UKDDamageGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 Level) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxNumThorns = 11;
};
