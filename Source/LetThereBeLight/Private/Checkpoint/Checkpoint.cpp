// Copyright ASKD Games


#include "Checkpoint/Checkpoint.h"
#include "Components/SphereComponent.h"



#include "GameFramework/PlayerStart.h"  

ACheckpoint::ACheckpoint(const FObjectInitializer& ObjectInitializer)
						: Super(ObjectInitializer)
{  
   PrimaryActorTick.bCanEverTick = false;

   Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
   Sphere->SetupAttachment(GetRootComponent());
   Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
   Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
   Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

   CheckpointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CheckpointMesh"));
   CheckpointMesh->SetupAttachment(Sphere);
   CheckpointMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
   CheckpointMesh->SetCollisionResponseToAllChannels(ECR_Block);

}

void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnSphereOverlap);
}

void ACheckpoint::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("Player")))
	{
		HandleGlowEffects();
	}
}

void ACheckpoint::HandleGlowEffects()
{
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UMaterialInstanceDynamic* DynamicMaterialInstance = UMaterialInstanceDynamic::Create(CheckpointMesh->GetMaterial(0), this);
	CheckpointMesh->SetMaterial(0, DynamicMaterialInstance);
	CheckpointReached(DynamicMaterialInstance);
}

