// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractiveActorBase.h"
#include "KDIntTorchesBeach.h"
#include "KDIntMainDoorBeach.generated.h"

//DECLARE_MULTICAST_DELEGATE_OneParam(FTorchLitDelegate, int32 /*TorchIndex*/);


class UStaticMeshComponent;
class UNiagaraComponent;
class UPointLightComponent;
class USceneComponent;
class UCapsuleComponent;
class UCameraShakeBase;
class USoundBase;
UCLASS()
class LETTHEREBELIGHT_API AKDIntMainDoorBeach : public AInteractiveActorBase
{
	GENERATED_BODY()

public:
	AKDIntMainDoorBeach();

	UPROPERTY(EditAnywhere, Category = "Torches")
	TArray<TObjectPtr<AKDIntTorchesBeach>> TorchesToWatch;

	//virtual void CanInteract_Implementation() override;
	//virtual void Interact_Implementation() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> Door1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> Door2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TObjectPtr<UNiagaraComponent> Door1Effect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TObjectPtr<UNiagaraComponent> Door2Effect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TSubclassOf<UCameraShakeBase> DoorOpenCameraShake;

	UPROPERTY(EditAnywhere, Category = "Audio")
	TObjectPtr<USoundBase> DoorOpeningSound;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TObjectPtr<UStaticMeshComponent> Torch1;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TObjectPtr<UStaticMeshComponent> Torch2;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	//TObjectPtr<UNiagaraComponent> Torch1Flame;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "Effects")
	//TObjectPtr<UNiagaraComponent> Torch2Flame;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TObjectPtr<UPointLightComponent> Torch1Light;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TObjectPtr<UPointLightComponent> Torch2Light;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TObjectPtr<UCapsuleComponent> Torch1Capsule;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TObjectPtr<UCapsuleComponent> Torch2Capsule;

private:

	bool bDoorsOpened = false;
	int32 LitTorchCount = 0;
	FTimerHandle DoorOpenTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Door")
	float DoorOpenElapsed = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Door")
	float DoorOpenDuration = 3.5f;

	UFUNCTION()
	void AnimateDoors();

	UFUNCTION()
	void OnTorchLit(AKDIntTorchesBeach* Torch);

	//bool bTorch1Lit = false;
	//bool bTorch2Lit = false;
	//FTorchLitDelegate OnTorchLit;

};
