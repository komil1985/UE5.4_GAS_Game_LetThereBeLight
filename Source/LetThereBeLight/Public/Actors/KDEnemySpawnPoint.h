// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "KDEnemySpawnPoint.generated.h"

class AEnemyCharacter;
/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API AKDEnemySpawnPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Class")
	TSubclassOf<AEnemyCharacter> EnemyClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Class")
	int32 EnemyLevel = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Class")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;
	
};
