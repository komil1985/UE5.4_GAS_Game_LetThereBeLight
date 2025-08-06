// Copyright ASKD Games


#include "Actors/KDInfoActorBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"

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

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(Mesh);

}

void AKDInfoActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AKDInfoActorBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Blue, OtherActor->GetName());
	if (OtherActor->Implements<UKDInteractable>())
	{
		IKDInteractable::Execute_Interact(this);
	}
}

void AKDInfoActorBase::Interact_Implementation()
{
	if (!bIsBig)
	{
		Mesh->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
	}
	else
	{
		Mesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	}
	bIsBig = true;
}
