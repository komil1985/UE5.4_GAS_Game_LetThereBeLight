// Copyright ASKD Games

#include "Characters/NPC/NPCCharacter.h"
#include "Components/WidgetComponent.h"
#include "Graph/MounteaDialogueGraph.h"
#include "Components/MounteaDialogueParticipant.h"

ANPCCharacter::ANPCCharacter()
{
	PromptWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PromptWidget"));
	PromptWidget->SetupAttachment(GetRootComponent());
	PromptWidget->SetVisibility(true);
	
	DialogueGraph = CreateDefaultSubobject<UMounteaDialogueGraph>("Dialogue Graph");
	DialogueParticipant = CreateDefaultSubobject<UMounteaDialogueParticipant>("Dialogue Participant");
	DialogueDataTable = CreateDefaultSubobject<UDataTable>("Dialogue DataTable");
	DialogueWidget = CreateDefaultSubobject<UUserWidget>(TEXT("Dialogue Widget"));
	
}

void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANPCCharacter::CanInteract_Implementation()
{
	if (IsValid(PromptWidget))
	{
		PromptWidget->SetVisibility(false);
	}
}

void ANPCCharacter::StopInteract_Implementation()
{
	if (IsValid(PromptWidget))
	{
		PromptWidget->SetVisibility(true);
	}
}

void ANPCCharacter::Interact_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Interact_Interface Activated"));
	if (IsValid(PromptWidget))
	{
		PromptWidget->SetVisibility(false);
	}
}

void ANPCCharacter::StartDialogue_Implementation(AActor* InstigatorActor)
{
	if (!DialogueGraph) return;

	if (IsValid(DialogueParticipant))
	{
		DialogueWidget->AddToViewport();
		DialogueWidget->SetVisibility(ESlateVisibility::Visible);
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Blue, "Dialogue Started");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Blue, "Dialogue Manager not initialized");
		return;
	}
}