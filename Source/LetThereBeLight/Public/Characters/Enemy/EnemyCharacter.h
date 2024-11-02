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
class LETTHEREBELIGHT_API AEnemyCharacter : public ABaseCharacter, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AEnemyCharacter();

	virtual void HighlightActor() override;		// Enemy Interface
	virtual void UnHighlightActor() override;	// End Enemy interface

	virtual int32 GetLevel() override;			// Combat Interface

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo () override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
};