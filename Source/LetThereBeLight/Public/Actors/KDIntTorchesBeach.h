// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractiveActorBase.h"
#include "KDIntTorchesBeach.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTorchLitSignature, AKDIntTorchesBeach*, Torch);

/**
 * 
 */
class USceneComponent;
class UStaticMeshComponent;
class UNiagaraComponent;
class UCapsuleComponent;
class UPointLightComponent;
UCLASS()
class LETTHEREBELIGHT_API AKDIntTorchesBeach : public AInteractiveActorBase
{
	GENERATED_BODY()

public: 
	AKDIntTorchesBeach();

	virtual void CanInteract_Implementation() override;
	virtual void Interact_Implementation() override;

	UPROPERTY()
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> Torch;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCapsuleComponent> TorchCapsule;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraComponent> TorchFlame;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPointLightComponent> TorchLight;

	UPROPERTY(BlueprintAssignable)
	FTorchLitSignature OnTorchLit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsTorchLit = false;

protected:
	virtual void BeginPlay() override;

};