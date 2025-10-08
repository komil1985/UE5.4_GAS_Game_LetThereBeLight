// Copyright ASKD Games


#include "Actors/KDIntMainDoorBeach.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraShakeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Sound/SoundBase.h"


AKDIntMainDoorBeach::AKDIntMainDoorBeach()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	SetRootComponent(SceneComponent);

	Door1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Left"));
	Door1->SetupAttachment(SceneComponent);
	Door1->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	Door2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Right"));
	Door2->SetupAttachment(SceneComponent);
	Door2->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	Door1Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Door1 Open Effect"));
	Door1Effect->SetupAttachment(Door1);
	Door1Effect->SetVisibility(false);

	Door2Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Door2 Open Effect"));
	Door2Effect->SetupAttachment(Door2);
	Door2Effect->SetVisibility(false);

}

void AKDIntMainDoorBeach::BeginPlay()
{
	Super::BeginPlay();

	LitTorchCount = 0;
	bDoorsOpened = false;

	for (auto Torch : TorchesToWatch)
	{
		if (Torch)
		{
			Torch->OnTorchLit.AddDynamic(this, &AKDIntMainDoorBeach::OnTorchLit);
			if (Torch->bIsTorchLit)
			{
				++LitTorchCount;
			}
		}
	}

	if (LitTorchCount == TorchesToWatch.Num())
	{
		OnTorchLit(nullptr);
	}

}

void AKDIntMainDoorBeach::AnimateDoors()
{
	const float DeltaTime = 0.01f;
	DoorOpenElapsed += DeltaTime;
	float Alpha = FMath::Clamp(DoorOpenElapsed / DoorOpenDuration, 0.f, 1.f);

	// Interpolate rotation from initial to desire degrees yaw
	FRotator Door1Rot = FMath::Lerp(FRotator(0.0f, -90.0f, 0.0f), FRotator(0.f, -180.0f, 0.f), Alpha);
	FRotator Door2Rot = FMath::Lerp(FRotator(0.0f, 90.0f, 0.0f), FRotator(0.f, 180.0f, 0.f), Alpha);

	if (Door1 && Door1Effect)
	{
		Door1->SetRelativeRotation(Door1Rot);
		Door1Effect->SetVisibility(true);
		if (Door1Rot == FRotator(0.0f, -180.0f, 0.0f))
		{
			Door1Effect->SetVisibility(false);
		}
	}
	if (Door2 && Door2Effect)
	{
		Door2->SetRelativeRotation(Door2Rot);
		Door2Effect->SetVisibility(true);
		if (Door2Rot == FRotator(0.0f, 180.0f, 0.0f))
		{
			Door2Effect->SetVisibility(false);
		}
	}

	if (Alpha >= 1.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(DoorOpenTimerHandle);
	}
}

void AKDIntMainDoorBeach::OnTorchLit(AKDIntTorchesBeach* Torch)
{
	++LitTorchCount;

	if (!bDoorsOpened && LitTorchCount == TorchesToWatch.Num())
	{
		bDoorsOpened = true;

		// Trigger camera shake on player controller
		APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
		if (PC && DoorOpenCameraShake)
		{
			PC->ClientStartCameraShake(DoorOpenCameraShake, 1.0f); // Shake scale at 1.0
		}

		// Play door opening sound at actor location
		if (DoorOpeningSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DoorOpeningSound, GetActorLocation());
		}

		GetWorld()->GetTimerManager().SetTimer(DoorOpenTimerHandle, this, &AKDIntMainDoorBeach::AnimateDoors, 0.01f, true);
		DoorOpenElapsed = 0.f;
	}
}
