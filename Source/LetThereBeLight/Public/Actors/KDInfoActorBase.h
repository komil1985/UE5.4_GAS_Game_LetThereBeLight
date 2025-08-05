// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KDInfoActorBase.generated.h"

class UStaticMeshComponent;
class UWidgetComponent;
UCLASS()
class LETTHEREBELIGHT_API AKDInfoActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AKDInfoActorBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr <UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr <UWidgetComponent> Widget;
};
