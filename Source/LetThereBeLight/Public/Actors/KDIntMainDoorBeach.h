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

	UFUNCTION()
	void AnimateDoors();
protected:

	UPROPERTY()
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> Door1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> Door2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> Torch1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> Torch2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraComponent> Torch1Flame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraComponent> Torch2Flame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UPointLightComponent> Torch1Light;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UPointLightComponent> Torch2Light;

private:

	bool bTorch1Lit = false;
	bool bTorch2Lit = false;
	bool bDoorsOpened = false;

	FTimerHandle DoorOpenTimerHandle;
	float DoorOpenElapsed = 0.0f;
	float DoorOpenDuration = 3.5f;

};
