// Copyright ASKD Games


#include "Actors/InteractiveActorBase.h"

AInteractiveActorBase::AInteractiveActorBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AInteractiveActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractiveActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

