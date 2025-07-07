// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "KDLevelStreamingVolume.generated.h"

class UBoxComponent;
class USceneComponent;
UCLASS()
class LETTHEREBELIGHT_API AKDLevelStreamingVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	AKDLevelStreamingVolume();

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent>BoxComponent;

	UPROPERTY()
	TObjectPtr<USceneComponent> SceneComponent;
};
