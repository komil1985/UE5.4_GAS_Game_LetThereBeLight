// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KDDialogueComponent.generated.h"

class UKDDialogueWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LETTHEREBELIGHT_API UKDDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UKDDialogueComponent();

	// The array of dialogue lines to cycle through
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<FText> DialogueLines;

	// The widget class to create for displaying dialogue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TSubclassOf<UUserWidget> DialogueWidgetClass;

	UPROPERTY()
	TObjectPtr<UKDDialogueWidget> CurrentDialogueWidget;

	// Call this to begin the dialogue sequence
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void StartDialogue();

	// Call this to advance to the next line of dialogue
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void AdvanceDialogue();

	int32 CurrentDialogueIndex;

protected:
	virtual void BeginPlay() override;

};
