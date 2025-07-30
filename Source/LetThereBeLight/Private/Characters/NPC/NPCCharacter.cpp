// Copyright ASKD Games


#include "Characters/NPC/NPCCharacter.h"
#include "Interactions/NPCInterface.h"
#include "Components/SphereComponent.h"
#include "Characters/Player/MyPlayerController.h"
#include "Characters/Player/PlayerCharacter.h"
#include "DialogueSystem/KDDialogueManager.h"


ANPCCharacter::ANPCCharacter()
{
	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetupAttachment(RootComponent);
	InteractionSphere->SetSphereRadius(300.0f);
	InteractionSphere->SetCollisionProfileName("Trigger");

}

void ANPCCharacter::Interact_Implementation(AActor* Caller)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(Caller)) {
		if (AKDDialogueManager* Manager = AKDDialogueManager::GetDialogueManager(GetWorld())) {
			Manager->StartDialogue(this);
		}
	}
}

void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();

	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPCCharacter::OnOverlapBegin);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &ANPCCharacter::OnOverlapEnd);
	
}

void ANPCCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMyPlayerController* PC = Cast<AMyPlayerController>(OtherActor))
	{
		if (OtherActor)
		{

		}
	}
}

void ANPCCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AMyPlayerController* PC = Cast<AMyPlayerController>(OtherActor))
	{
		if (!OtherActor)
		{

		}
	}
}
