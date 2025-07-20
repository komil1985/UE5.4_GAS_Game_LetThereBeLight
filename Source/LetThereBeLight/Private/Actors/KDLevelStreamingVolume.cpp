// Copyright ASKD Games


#include "Actors/KDLevelStreamingVolume.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

AKDLevelStreamingVolume::AKDLevelStreamingVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
	SceneComponent->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(SceneComponent);

	bGenerateOverlapEventsDuringLevelStreaming = true;
}


void AKDLevelStreamingVolume::BeginPlay()
{
	Super::BeginPlay();
}
