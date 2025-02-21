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
	
	virtual void Die() override;														//  <-- Combat Interface
	virtual int32 GetPlayerLevel_Implementation() override;								//  <-- Combat Interface

	virtual void AddToXP_Implementation(int32 InXP) override;							//  <-- Player Interface
	virtual void LevelUp_Implementation() override;										//  <-- Player Interface
	virtual int32 GetXP_Implementation() const override;								//  <-- Player Interface
	virtual int32 FindLevelForXP_Implementation(int32 InXP) const override;				//  <-- Player Interface
	virtual int32 GetAttributePointsReward_Implementation(int32 Level) const override;	//  <-- Player Interface
	virtual int32 GetSpellPointsReward_Implementation(int32 Level) const override;		//  <-- Player Interface
	virtual void AddToPlayerLevel_Implementation(int32 InPlayerLevel) override;			//  <-- Player Interface	
	virtual void AddToAttributePoints_Implementation(int32 InAttributePoints) override; //  <-- Player Interface
	virtual void AddToSpellPoints_Implementation(int32 InSpellPoints) override;			//  <-- Player Interface

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.0f;

private:
	virtual void InitAbilityActorInfo() override;
};
