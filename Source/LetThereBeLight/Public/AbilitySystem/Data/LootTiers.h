// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LootTiers.generated.h"


USTRUCT(BlueprintType)
struct FLootItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LootTiers|Spawning")
	TSubclassOf<AActor> LootClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LootTiers|Spawning")
	float ChanceToSpawn = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LootTiers|Spawning")
	int32 MaxNumberToSpawn = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LootTiers|Spawning")
	bool bLootLevelOverride = true;

};

/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API ULootTiers : public UDataAsset
{
	GENERATED_BODY()

public:
	TArray<FLootItem> GetLootItems();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LootTires|Spawning")
	TArray<FLootItem> LootItems;
	
};
