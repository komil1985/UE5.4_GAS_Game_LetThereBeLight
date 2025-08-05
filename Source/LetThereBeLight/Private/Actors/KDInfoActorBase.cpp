// Copyright ASKD Games


#include "Actors/KDInfoActorBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

AKDInfoActorBase::AKDInfoActorBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(Mesh);
	Widget->SetVisibility(false);

}

void AKDInfoActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}


