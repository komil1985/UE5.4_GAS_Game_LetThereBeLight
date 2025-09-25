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

	Torch2Flame = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Torch Right Flame"));
	Torch2Flame->SetupAttachment(Torch2);

	Torch1Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Torch Left Light"));
	Torch1Light->SetupAttachment(Torch1);

	Torch2Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Torch Right Light"));
	Torch2Light->SetupAttachment(Torch2);
}

void AKDIntMainDoorBeach::CanInteract_Implementation()
{
}

void AKDIntMainDoorBeach::Interact_Implementation()
{
}
