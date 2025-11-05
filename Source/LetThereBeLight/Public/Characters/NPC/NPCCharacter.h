// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interactions/NPCInterface.h"
#include "Interactions/KDInteractable.h"
#include "NPCCharacter.generated.h"

class UWidgetComponent;
class UMounteaDialogueParticipant;
class UBoxComponent;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue | Participant")
	TObjectPtr<UMounteaDialogueParticipant> DialogueParticipant;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TSubclassOf<AActor> DialogueActor;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	TSubclassOf<AActor> GetDialogueActor() { return DialogueActor; }


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	TWeakObjectPtr<ACharacter> OverlappingPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr <UWidgetComponent> PromptWidget;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	TObjectPtr<UBoxComponent> ProximityBox;

	UPROPERTY(EditAnywhere, Category = "Mesh Rotation")
	float MeshRotationInterpSpeed = 1.0f;

	UFUNCTION()
	virtual void OnProxomityBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void OnProximityBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	FTimerHandle NpcRotationTimer;
	float NpcRotateElapsed = 0.0f;
	float NpcRotateDuration = 60.0f;

	UFUNCTION()
	void NpcRotateToPlayer();
};
