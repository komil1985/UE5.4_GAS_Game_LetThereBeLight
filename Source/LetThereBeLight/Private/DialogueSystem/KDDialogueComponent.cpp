// Copyright ASKD Games


#include "DialogueSystem/KDDialogueComponent.h"
#include "UI/Widget/KDDialogueWidget.h"
#include "Kismet\GameplayStatics.h"

UKDDialogueComponent::UKDDialogueComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentDialogueIndex = 0;
}


void UKDDialogueComponent::StartDialogue()
{
	// Make sure we have dialogue lines to show
	if (DialogueLines.Num() == 0 || !DialogueWidgetClass) return;

	// Reset index to start from the beginning
	CurrentDialogueIndex = 0;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (PlayerController)
	{
		if (CurrentDialogueWidget)
		{
			CurrentDialogueWidget->RemoveFromParent();
		}
		CurrentDialogueWidget = CreateWidget<UKDDialogueWidget>(PlayerController, DialogueWidgetClass);
		if (CurrentDialogueWidget)
		{
			CurrentDialogueWidget->AddToViewport();
			AdvanceDialogue();		// Display the first line immediately
		}
	}

}

void UKDDialogueComponent::AdvanceDialogue()
{
	if (!CurrentDialogueWidget) return; 

	if (CurrentDialogueIndex < DialogueLines.Num())
	{
		// Display the nexxt line of dialogue
		CurrentDialogueWidget->SetDilogueText(DialogueLines[CurrentDialogueIndex]);
		CurrentDialogueIndex++;
	}
	else
	{
		//End of dialogue, remoce widget from screen
		CurrentDialogueWidget->RemoveFromParent();
		CurrentDialogueWidget = nullptr;
	}
}

void UKDDialogueComponent::BeginPlay()
{
	Super::BeginPlay();

}


