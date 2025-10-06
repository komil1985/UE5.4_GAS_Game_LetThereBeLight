// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractiveActorBase.h"
#include "KDIntTorchesBeach.generated.h"

//DECLARE_MULTICAST_DELEGATE_OneParam(FTorchLitDelegate, int32 /*TorchIndex*/);
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
	TObjectPtr<UStaticMeshComponent> Torch1;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> Torch2;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCapsuleComponent> Torch1Capsule;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCapsuleComponent> Torch2Capsule;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraComponent> Torch1Flame;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraComponent> Torch2Flame;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPointLightComponent> Torch1Light;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPointLightComponent> Torch2Light;

	UPROPERTY(BlueprintAssignable)
	FTorchLitSignature OnTorchLit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bTorch1Lit = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bTorch2Lit = false;

	//FTorchLitDelegate OnTorchLit;

protected:
	virtual void BeginPlay() override;

};