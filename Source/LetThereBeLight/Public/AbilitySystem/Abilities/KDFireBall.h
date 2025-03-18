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
	
	UFUNCTION(BlueprintCallable)
	void SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride, AActor* HomingTarget);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "FireBall")
	float ProjectileSpread = 90.0f;

	UPROPERTY(EditDefaultsOnly, Category = "FireBall")
	int32 MaxNumProjectiles = 5;

	UPROPERTY(EditDefaultsOnly, Category = "FireBall")
	float HomingAccelerationMin = 1500.0f;

	UPROPERTY(EditDefaultsOnly, Category = "FireBall")
	float HomingAccelerationMax = 3000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "FireBall")
	bool bLaunchHomingProjectiles = true;
};
