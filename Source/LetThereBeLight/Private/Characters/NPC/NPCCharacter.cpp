// Copyright ASKD Games

#include "Characters/NPC/NPCCharacter.h"
#include "Components/WidgetComponent.h"
#include "Components/MounteaDialogueParticipant.h"
#include "Engine/DataTable.h"
#include <Kismet/GameplayStatics.h>

ANPCCharacter::ANPCCharacter()
{
	PromptWidget = CreateDefaultSubobject<UWidgetComponent>("PromptWidget");
	PromptWidget->SetupAttachment(RootComponent);
	PromptWidget->SetVisibility(true);

	DialogueWidget = CreateDefaultSubobject<UUserWidget>("DialogueWidget");
	DialogueParticipant = CreateDefaultSubobject<UMounteaDialogueParticipant>("Dialogue Participant");
	DialogueDataTable = CreateDefaultSubobject<UDataTable>("Dialogue DataTable");
	
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
	if (IsValid(DialogueParticipant))
	{
		UObject* WorldContextObject = GetWorld();
		if (IsValid(InstigatorActor))
		{
			InstigatorActor = UGameplayStatics::GetActorOfClass(WorldContextObject, DialogueActor);
			InstigatorActor->GetComponentByClass(DialogueParticipant->GetClass());
			return;
		}
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Blue, "Dialogue Started");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Blue, "Dialogue Manager not initialized");
		return;
	}
}