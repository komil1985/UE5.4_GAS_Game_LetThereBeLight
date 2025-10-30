// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interactions/NPCInterface.h"
#include "Interactions/KDInteractable.h"
#include "NPCCharacter.generated.h"

class UWidgetComponent;
class UUserWidget;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TSubclassOf<ACharacter> DialogueActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TSubclassOf<UMounteaDialogueParticipant> Participant;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue | Participant")
	TObjectPtr<UMounteaDialogueParticipant> DialogueParticipant;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr <UWidgetComponent> PromptWidget;

	UPROPERTY(EditAnywhere, Category = "Dialogue")
	TObjectPtr<UDataTable> DialogueDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TObjectPtr<UUserWidget> DialogueWidget;
};
