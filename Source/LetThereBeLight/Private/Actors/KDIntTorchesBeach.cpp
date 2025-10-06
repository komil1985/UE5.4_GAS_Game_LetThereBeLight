// Copyright ASKD Games


#include "Actors/KDIntTorchesBeach.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"
#include "Components/PointLightComponent.h"

AKDIntTorchesBeach::AKDIntTorchesBeach()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(SceneComponent);

	Torch1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Torch 1"));
	Torch1->SetupAttachment(SceneComponent);

	Torch2= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Torch 2"));
	Torch2->SetupAttachment(SceneComponent);

	Torch1Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Torch 1 Capsule Component"));
	Torch1Capsule->SetupAttachment(Torch1);

	Torch2Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Torch 2 Capsule Component"));
	Torch2Capsule->SetupAttachment(Torch2);

	Torch1Flame = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Torch 1 Flame"));
	Torch1Flame->SetupAttachment(Torch1);
	Torch1Flame->SetVisibility(false);

	Torch2Flame = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Torch 2 Flame"));
	Torch2Flame->SetupAttachment(Torch2);
	Torch2Flame->SetVisibility(false);

	Torch1Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Torch 1 Light"));
	Torch1Light->SetupAttachment(Torch1);
	Torch1Light->SetVisibility(false);

	Torch2Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Torch 2 Light"));
	Torch2Light->SetupAttachment(Torch2);
	Torch2Light->SetVisibility(false);

}

void AKDIntTorchesBeach::BeginPlay()
{
	Super::BeginPlay();

	Torch1Light->SetVisibility(bTorch1Lit);
	Torch2Light->SetVisibility(bTorch2Lit);

	Torch1Flame->SetVisibility(bTorch1Lit);
	Torch2Flame->SetVisibility(bTorch2Lit);
}

void AKDIntTorchesBeach::CanInteract_Implementation()
{
	if (!bTorch1Lit || !bTorch2Lit)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0, FColor::Cyan, TEXT("Can_Interact: Torch available to light"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0, FColor::Cyan, TEXT("Cannot interact: Doors already opened"));
	}
}

void AKDIntTorchesBeach::Interact_Implementation()
{
	// Light Torch 1 if unlit
	if (Torch1 && !bTorch1Lit)
	{
		bTorch1Lit = true;
		Torch1Flame->SetVisibility(true);
		Torch1Light->SetVisibility(true);
		OnTorchLit.Broadcast(this);
		GEngine->AddOnScreenDebugMessage(1, 5.0, FColor::Cyan, TEXT("Torch 1 lit"));
		return;  // Allow one interaction per call
	}

	// Light Torch 2 if unlit
	if (Torch2 && !bTorch2Lit)
	{
		bTorch2Lit = true;
		Torch2Flame->SetVisibility(true);
		Torch2Light->SetVisibility(true);
		OnTorchLit.Broadcast(this);
		GEngine->AddOnScreenDebugMessage(1, 5.0, FColor::Cyan, TEXT("Torch 2 lit"));
		return;
	}
}
