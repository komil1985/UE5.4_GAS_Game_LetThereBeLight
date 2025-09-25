// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractiveActorBase.h"
#include "KDIntMainDoorBeach.generated.h"

class UStaticMeshComponent;
class UNiagaraComponent;
class UPointLightComponent;
class USceneComponent;
UCLASS()
class LETTHEREBELIGHT_API AKDIntMainDoorBeach : public AInteractiveActorBase
{
	GENERATED_BODY()

public:
	AKDIntMainDoorBeach();
	virtual void CanInteract_Implementation() override;
	virtual void Interact_Implementation() override;

protected:

	UPROPERTY()
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> Door1;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> Door2;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> Torch1;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> Torch2;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraComponent> Torch1Flame;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraComponent> Torch2Flame;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPointLightComponent> Torch1Light;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPointLightComponent> Torch2Light;

};
