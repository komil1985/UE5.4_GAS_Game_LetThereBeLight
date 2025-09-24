// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractiveActorBase.h"
#include "KDIntMainDoorBeach.generated.h"

class UStaticMeshComponent;
class UNiagaraComponent;
class UPointLightComponent;
UCLASS()
class LETTHEREBELIGHT_API AKDIntMainDoorBeach : public AInteractiveActorBase
{
	GENERATED_BODY()

public:
	AKDIntMainDoorBeach();
	virtual void CanInteract_Implementation() override;
	virtual void Interact_Implementation() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> Door1;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> Door2;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> Torch1;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> Torch2;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraComponent> Torch1Flame;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraComponent> Torch2Flame;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPointLightComponent> Torch1Light;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPointLightComponent> Torch2Light;

};
