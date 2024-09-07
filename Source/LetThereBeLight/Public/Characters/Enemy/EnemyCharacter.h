// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Characters/Base/BaseCharacter.h"
#include "Interactions/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	virtual void HighlightActor();
	virtual void UnhighlightActor();
};
