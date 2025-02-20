// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Characters/Base/BaseCharacter.h"
#include "Interactions/PlayerInterface.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API APlayerCharacter : public ABaseCharacter, public IPlayerInterface
{
	GENERATED_BODY()
public:
	APlayerCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void Die() override;				//	<-- Combat Interface
	virtual int32 GetPlayerLevel() override;	//  <-- Combat Interface
	virtual void AddToXP_Implementation(int32 InXP) override;	//  <-- Player Interface

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.0f;

private:
	virtual void InitAbilityActorInfo() override;
};
