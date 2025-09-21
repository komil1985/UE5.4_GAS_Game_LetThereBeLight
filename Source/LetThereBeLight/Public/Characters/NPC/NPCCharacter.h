// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interactions/NPCInterface.h"
#include "Interactions/KDInteractable.h"
#include "NPCCharacter.generated.h"

class UWidgetComponent;
UCLASS()
class LETTHEREBELIGHT_API ANPCCharacter : public ACharacter, public INPCInterface, public IKDInteractable
{
	GENERATED_BODY()

public:
	ANPCCharacter();

	virtual void CanInteract_Implementation() override;
	virtual void StopInteract_Implementation() override;

	UFUNCTION()
	virtual void Interact_Implementation() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr <UWidgetComponent> Widget;

};
