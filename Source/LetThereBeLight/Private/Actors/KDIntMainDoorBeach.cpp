// Copyright ASKD Games


#include "Actors/KDIntMainDoorBeach.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraShakeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"


AKDIntMainDoorBeach::AKDIntMainDoorBeach()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	SetRootComponent(SceneComponent);

	Door1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Left"));
	Door1->SetupAttachment(SceneComponent);
	Door1->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	Door2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Right"));
	Door2->SetupAttachment(SceneComponent);
	Door2->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	Torch1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Torch Left"));
	Torch1->SetupAttachment(SceneComponent);

	Torch2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Torch Right"));
	Torch2->SetupAttachment(SceneComponent);

	Torch1Flame = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Torch Left Flame"));
	Torch1Flame->SetupAttachment(Torch1);
	Torch1Flame->SetVisibility(false);

	Torch2Flame = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Torch Right Flame"));
	Torch2Flame->SetupAttachment(Torch2);
	Torch2Flame->SetVisibility(false);

	Torch1Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Torch Left Light"));
	Torch1Light->SetupAttachment(Torch1);
	Torch1Light->SetVisibility(false);

	Torch2Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Torch Right Light"));
	Torch2Light->SetupAttachment(Torch2);
	Torch2Light->SetVisibility(false);

	Door1Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Door1 Open Effect"));
	Door1Effect->SetupAttachment(Door1);
	Door1Effect->SetVisibility(false);

	Door2Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Door2 Open Effect"));
	Door2Effect->SetupAttachment(Door2);
	Door2Effect->SetVisibility(false);

	Torch1Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Torch1 Capsule Component"));
	Torch1Capsule->SetupAttachment(Torch1);

	Torch2Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Torch2 Capsule Component"));
	Torch2Capsule->SetupAttachment(Torch2);
}

void AKDIntMainDoorBeach::CanInteract_Implementation()
{
	if (!bTorch1Lit || !bTorch2Lit)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0, FColor::Cyan, TEXT("Can_Interact: Torch available to light"));
	}
	else if (!bDoorsOpened)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0, FColor::Cyan, TEXT("Can_Interact: Both torches lit, doors can open"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0, FColor::Cyan, TEXT("Cannot interact: Doors already opened"));
	}

}

void AKDIntMainDoorBeach::Interact_Implementation()
{
	// Light Torch 1 if unlit
	if (!bTorch1Lit && Torch1Flame && Torch1Light)
	{
		bTorch1Lit = true;
		Torch1Flame->SetVisibility(true);
		Torch1Light->SetVisibility(true);
		GEngine->AddOnScreenDebugMessage(1, 5.0, FColor::Cyan, TEXT("Torch 1 lit"));
		return;  // Allow one interaction per call
	}

	// Light Torch 2 if unlit
	if (!bTorch2Lit && Torch2Flame && Torch2Light)
	{
		bTorch2Lit = true;
		Torch2Flame->SetVisibility(true);
		Torch2Light->SetVisibility(true);
		GEngine->AddOnScreenDebugMessage(1, 5.0, FColor::Cyan, TEXT("Torch 2 lit"));
		return;
	}

	// Open doors once both torches are lit and doors not opened
	if (bTorch1Lit && bTorch2Lit && !bDoorsOpened)
	{
		bDoorsOpened = true;

		// Trigger camera shake on player controller
		APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
		if (PC && DoorOpenCameraShake)
		{
			PC->ClientStartCameraShake(DoorOpenCameraShake, 1.0f); // Shake scale at 1.0
		}

		GetWorld()->GetTimerManager().SetTimer(DoorOpenTimerHandle, this, &AKDIntMainDoorBeach::AnimateDoors, 0.01f, true);
		DoorOpenElapsed = 0.f;
		GEngine->AddOnScreenDebugMessage(1, 5.0, FColor::Cyan, TEXT("Both torches lit. Doors opening"));
		Door1Effect->SetVisibility(false);
		Door2Effect->SetVisibility(false);
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
	}
	if (Door2 && Door2Effect)
	{
		Door2->SetRelativeRotation(Door2Rot);
		Door2Effect->SetVisibility(true);
	}

	if (Alpha >= 1.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(DoorOpenTimerHandle);
	}
}
