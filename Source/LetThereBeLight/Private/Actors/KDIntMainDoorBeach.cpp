// Copyright ASKD Games


#include "Actors/KDIntMainDoorBeach.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "Components/PointLightComponent.h"


AKDIntMainDoorBeach::AKDIntMainDoorBeach()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	SetRootComponent(SceneComponent);

	Door1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Left"));
	Door1->SetupAttachment(SceneComponent);

	Door2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Right"));
	Door2->SetupAttachment(SceneComponent);

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
		GetWorld()->GetTimerManager().SetTimer(DoorOpenTimerHandle, this, &AKDIntMainDoorBeach::AnimateDoors, 0.01f, true);
		DoorOpenElapsed = 0.f;
		GEngine->AddOnScreenDebugMessage(1, 5.0, FColor::Cyan, TEXT("Both torches lit. Doors opening"));
	}
}

void AKDIntMainDoorBeach::AnimateDoors()
{
	const float DeltaTime = 0.01f;
	DoorOpenElapsed += DeltaTime;
	float Alpha = FMath::Clamp(DoorOpenElapsed / DoorOpenDuration, 0.f, 1.f);

	// Interpolate rotation from 0 to 90 degrees yaw
	FRotator Door1Rot = FMath::Lerp(FRotator::ZeroRotator, FRotator(0.f, 90.f, 0.f), Alpha);
	FRotator Door2Rot = FMath::Lerp(FRotator::ZeroRotator, FRotator(0.f, -90.f, 0.f), Alpha);

	if (Door1) Door1->SetRelativeRotation(Door1Rot);
	if (Door2) Door2->SetRelativeRotation(Door2Rot);

	if (Alpha >= 1.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(DoorOpenTimerHandle);
	}
}
