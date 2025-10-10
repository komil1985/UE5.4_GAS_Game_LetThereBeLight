// Copyright ASKD Games


#include "Characters/NPC/NPCCharacter.h"
#include "Components/WidgetComponent.h"


ANPCCharacter::ANPCCharacter()
{
	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(GetRootComponent());
	Widget->SetVisibility(false);
}

void ANPCCharacter::StartDialogue_Implementation()
{
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

void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();
}
