// Copyright ASKD Games


#include "Actors/KDEnemySpawnVolume.h"

AKDEnemySpawnVolume::AKDEnemySpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AKDEnemySpawnVolume::LoadActor_Implementation()
{
}

void AKDEnemySpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

void AKDEnemySpawnVolume::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}


