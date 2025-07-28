// Copyright ASKD Games


#include "Characters/NPC/NPCCharacter.h"
#include "Components/SphereComponent.h"

ANPCCharacter::ANPCCharacter()
{
	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetupAttachment(RootComponent);
	InteractionSphere->SetSphereRadius(300.0f);
	InteractionSphere->SetCollisionProfileName("Trigger");

}

void ANPCCharacter::Interact_Implementation(AActor* Caller)
{
}

void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();

	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPCCharacter::OnOverlapBegin);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &ANPCCharacter::OnOverlapEnd);
	
}

void ANPCCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ANPCCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}



