// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractiveActorBase.h"
#include "KDIntTorchesBeach.h"
#include "KDIntMainDoorBeach.generated.h"


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

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Torches")
	TArray<TObjectPtr<AKDIntTorchesBeach>> TorchesToWatch;

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

private:

	bool bDoorsOpened = false;
	int32 LitTorchCount = 0;
	FTimerHandle DoorOpenTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Door")
	float DoorOpenElapsed = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Door")
	float DoorOpenDuration = 6.5f;

	UFUNCTION()
	void AnimateDoors();

	UFUNCTION()
	void OnTorchLit(AKDIntTorchesBeach* Torch);

};
