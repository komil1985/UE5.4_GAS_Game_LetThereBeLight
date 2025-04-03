// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/KDDamageGameplayAbility.h"
#include "KDFireBlast.generated.h"

/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API UKDFireBlast : public UKDDamageGameplayAbility
{
	GENERATED_BODY()

public:
	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 Level) override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "FrireBlast")
	int32 NumFireBalls = 10;
	
};
