// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactions/KDInteractable.h"
#include "InteractiveActorBase.generated.h"


UCLASS()
class LETTHEREBELIGHT_API AInteractiveActorBase : public AActor, public IKDInteractable
{
	GENERATED_BODY()
	
public:	
	AInteractiveActorBase();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;	

};
