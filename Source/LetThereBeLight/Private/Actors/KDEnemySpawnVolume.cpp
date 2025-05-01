// Copyright ASKD Games


#include "Actors/KDEnemySpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Interactions/PlayerInterface.h"
#include "Actors/KDEnemySpawnPoint.h"


AKDEnemySpawnVolume::AKDEnemySpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetupAttachment(GetRootComponent());
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionObjectType(ECC_WorldStatic);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AKDEnemySpawnVolume::LoadActor_Implementation()
{
	if (bReached)
	{
		Destroy();
	}
}

void AKDEnemySpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AKDEnemySpawnVolume::OnBoxOverlap);
	
}

void AKDEnemySpawnVolume::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UPlayerInterface>()) return;

	bReached = true;

	for (AKDEnemySpawnPoint* Point : SpawnPoints)
	{
		if (IsValid(Point))
		{
			Point->SpawnEnemy();
		}
	}
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
