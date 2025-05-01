// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactions/SaveInterface.h"
#include "KDEnemySpawnVolume.generated.h"

class UBoxComponent;
class AKDEnemySpawnPoint;
UCLASS()
class LETTHEREBELIGHT_API AKDEnemySpawnVolume : public AActor, public ISaveInterface
{
	GENERATED_BODY()
	
public:	
	AKDEnemySpawnVolume();

	/* Save Interface */
	virtual void LoadActor_Implementation() override;
	/*end Save Interface*/

	UPROPERTY(BlueprintReadOnly, SaveGame)
	bool bReached = false;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	TArray<AKDEnemySpawnPoint*> SpawnPoints;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxComponent;


};
