// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/KDGameplayAbility.h"
#include "KDSummonAbility.generated.h"

/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API UKDSummonAbility : public UKDGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocation();

	UFUNCTION(BlueprintPure, Category = "Summoning")
	TSubclassOf<APawn> GetRandomMinionClass();

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	int32 NumMinions = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	TArray<TSubclassOf<APawn>> MinionClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	float MinSpawnDistance = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	float MaxSpawnDistance = 250.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	float SpawnRadius = 90.0f;
};
