// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/KDDamageGameplayAbility.h"
#include "KDFireBlast.generated.h"


class AKDProjectileFireBall;

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

	UFUNCTION(BlueprintCallable)
	TArray<AKDProjectileFireBall*> SpawnFireBalls();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "FireBlast")
	int32 NumFireBalls = 10;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AKDProjectileFireBall> ProjectileFireBallClass;
	
};
