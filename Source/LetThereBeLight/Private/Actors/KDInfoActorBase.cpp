// Copyright ASKD Games


#include "Actors/KDInfoActorBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"

AKDInfoActorBase::AKDInfoActorBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(Mesh);
	Widget->SetVisibility(false);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(Mesh);

}

void AKDInfoActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKDInfoActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AKDInfoActorBase::Interact_Implementation()
{
	if (!bIsBig)
	{
		Mesh->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));
	}
	else
	{
		Mesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	}
	bIsBig = !bIsBig;
}
