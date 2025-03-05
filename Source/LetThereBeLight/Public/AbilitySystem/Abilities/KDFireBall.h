// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/KDProjectileSpell.h"
#include "KDFireBall.generated.h"

/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API UKDFireBall : public UKDProjectileSpell
{
	GENERATED_BODY()
	
public:
	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 Level) override;
};
