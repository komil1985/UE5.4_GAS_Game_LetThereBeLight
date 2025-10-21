// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interactions/NPCInterface.h"
#include "Interactions/KDInteractable.h"
#include "NPCCharacter.generated.h"

class UWidgetComponent;
class UMounteaDialogueGraph;
class UMounteaDialogueParticipant;
class UDataTable;
UCLASS()
class LETTHEREBELIGHT_API ANPCCharacter : public ACharacter, public INPCInterface, public IKDInteractable
{
	GENERATED_BODY()

public:
	ANPCCharacter();

	// INPCInterface
	virtual void CanInteract_Implementation() override;
	virtual void StopInteract_Implementation() override;
	virtual void StartDialogue_Implementation(AActor* InstigatorActor) override;

	// IKDInteractable
	virtual void Interact_Implementation() override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr <UWidgetComponent> PromptWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	TObjectPtr <UUserWidget> DialogueWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	TObjectPtr<UDataTable> DialogueDataTable;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	TObjectPtr<UMounteaDialogueGraph> DialogueGraph;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue | Participant")
	TObjectPtr<UMounteaDialogueParticipant> DialogueParticipant;

};
