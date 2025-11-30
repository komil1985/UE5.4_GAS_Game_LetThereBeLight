// Copyright ASKD Games


#include "Actors/KDIntTorchesBeach.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"
#include "Components/PointLightComponent.h"

AKDIntTorchesBeach::AKDIntTorchesBeach()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(SceneComponent);

	Torch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Torch"));
	Torch->SetupAttachment(SceneComponent);

	TorchCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Torch Capsule Component"));
	TorchCapsule->SetupAttachment(Torch);

	TorchFlame = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Torch Flame"));
	TorchFlame->SetupAttachment(Torch);
	TorchFlame->SetVisibility(false);

	TorchLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Torch Light"));
	TorchLight->SetupAttachment(Torch);
	TorchLight->SetVisibility(false);

}

void AKDIntTorchesBeach::BeginPlay()
{
	Super::BeginPlay();

	TorchLight->SetVisibility(bIsTorchLit);
	TorchFlame->SetVisibility(bIsTorchLit);
}

void AKDIntTorchesBeach::CanInteract_Implementation()
{
	if (!bIsTorchLit)
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
	// Light Torch if unlit
	if (Torch && !bIsTorchLit)
	{
			bIsTorchLit = true;
			TorchFlame->SetVisibility(true);
			TorchLight->SetVisibility(true);
			OnTorchLit.Broadcast(this);
			GEngine->AddOnScreenDebugMessage(1, 5.0, FColor::Cyan, TEXT("Torches lit"));
			return;  // Allow one interaction per call	
	}
}
