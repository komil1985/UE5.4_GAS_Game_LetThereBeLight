// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interactions/NPCInterface.h"
#include "NPCCharacter.generated.h"


UCLASS()
class LETTHEREBELIGHT_API ANPCCharacter : public ACharacter, public INPCInterface
{
	GENERATED_BODY()

public:
	ANPCCharacter();

protected:
	virtual void BeginPlay() override;

};
