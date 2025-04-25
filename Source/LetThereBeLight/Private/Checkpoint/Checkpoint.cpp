// Copyright ASKD Games


#include "Checkpoint/Checkpoint.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PlayerStart.h"  
#include "Interactions/PlayerInterface.h"
#include "GameMode/MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"


ACheckpoint::ACheckpoint(const FObjectInitializer& ObjectInitializer)
						: Super(ObjectInitializer)
{  
   PrimaryActorTick.bCanEverTick = false;

   CheckpointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CheckpointMesh"));
   CheckpointMesh->SetupAttachment(GetRootComponent());
   CheckpointMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
   CheckpointMesh->SetCollisionResponseToAllChannels(ECR_Block);
   CheckpointMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_TAN);
   CheckpointMesh->MarkRenderStateDirty();

   Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
   Sphere->SetupAttachment(CheckpointMesh);
   Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
   Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
   Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

   MoveToComponent = CreateDefaultSubobject<USceneComponent>(TEXT("MoveToComponent"));
   MoveToComponent->SetupAttachment(GetRootComponent());

}

void ACheckpoint::LoadActor_Implementation()
{
	if (bReached)
	{
		HandleGlowEffects();
	}
}

void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();

	if (bBindOverlapCallback)
	{
		Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnSphereOverlap);
	}
}

void ACheckpoint::SetMoveToLocation_Implementation(FVector& OutDestination)
{
	OutDestination = MoveToComponent->GetComponentLocation();
}

void ACheckpoint::HighlightActor_Implementation()
{
	if(!bReached)
	{
		CheckpointMesh->SetRenderCustomDepth(true);
	}
}

void ACheckpoint::UnHighlightActor_Implementation()
{
	CheckpointMesh->SetRenderCustomDepth(false);
}

void ACheckpoint::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UPlayerInterface>())
	{
		bReached = true;

		if (AMyGameModeBase* KDGM = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this)))
		{
			KDGM->SaveWorldState(GetWorld());
		}

		IPlayerInterface::Execute_SaveProgress(OtherActor, PlayerStartTag);
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

