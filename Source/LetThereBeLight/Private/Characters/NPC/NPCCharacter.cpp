// Copyright ASKD Games

#include "Characters/NPC/NPCCharacter.h"
#include "Components/WidgetComponent.h"
#include "Components/MounteaDialogueManager.h"
#include "Graph/MounteaDialogueGraph.h"
#include "Components/MounteaDialogueParticipant.h"


ANPCCharacter::ANPCCharacter()
{
	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(GetRootComponent());
	Widget->SetVisibility(false);
	
	DialogueGraph = CreateDefaultSubobject<UMounteaDialogueGraph>("Dialogue Graph");
	DialogueParticipant = CreateDefaultSubobject<UMounteaDialogueParticipant>("Dialogue Participant");
}

void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

void ANPCCharacter::StartDialogue_Implementation(AActor* InteractingActor)
{
	DialogueManager = NewObject<UMounteaDialogueManager>(this);
	if (DialogueManager)
	{
		if (DialogueGraph)
		{
			//DialogueGraph->StartNode;
			GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Blue, "Dialogue Started");
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Blue, "Dialogue Manager not initialized");
	}
}

void ANPCCharacter::CanInteract_Implementation()
{
	if (IsValid(Widget))
	{
		Widget->SetVisibility(false);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Can_Interface Activated"));
	}
}

void ANPCCharacter::StopInteract_Implementation()
{
	if (IsValid(Widget))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Stop_Interface Activated"));
		Widget->SetVisibility(true);
	}
}

void ANPCCharacter::Interact_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Interact_Interface Activated"));
	if (IsValid(Widget))
	{
		Widget->SetVisibility(false);
	}
}
