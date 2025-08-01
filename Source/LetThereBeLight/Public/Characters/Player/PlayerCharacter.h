// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Characters/Base/BaseCharacter.h"
#include "Interactions/PlayerInterface.h"
#include "Interactions/KDInteractable.h"
#include "PlayerCharacter.generated.h"

class UNiagaraComponent;
class UCameraComponent;
class USpringArmComponent;
class UBoxComponent;
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

	virtual void Die(const FVector& DeathImpulse) override;										//  <-- Combat Interface
	virtual int32 GetPlayerLevel_Implementation() override;										//  <-- Combat Interface

	virtual void AddToXP_Implementation(int32 InXP) override;									//  <-- Player Interface
	virtual void LevelUp_Implementation() override;												//  <-- Player Interface
	virtual int32 GetXP_Implementation() const override;										//  <-- Player Interface
	virtual int32 FindLevelForXP_Implementation(int32 InXP) const override;						//  <-- Player Interface
	virtual int32 GetAttributePointsReward_Implementation(int32 Level) const override;			//  <-- Player Interface
	virtual int32 GetSpellPointsReward_Implementation(int32 Level) const override;				//  <-- Player Interface
	virtual void AddToPlayerLevel_Implementation(int32 InPlayerLevel) override;					//  <-- Player Interface	
	virtual void AddToAttributePoints_Implementation(int32 InAttributePoints) override;			//  <-- Player Interface
	virtual void AddToSpellPoints_Implementation(int32 InSpellPoints) override;					//  <-- Player Interface
	virtual int32 GetAttributePoints_Implementation() const override;							//  <-- Player Interface
	virtual int32 GetSpellPoints_Implementation() const override;								//  <-- Player Interface
	virtual void ShowMagicCircle_Implementation(UMaterialInterface* DecalMaterial) override;	//  <-- Player Interface
	virtual void HideMagicCircle_Implementation() override;										//  <-- Player Interface
	virtual void SaveProgress_Implementation(const FName& CheckpointTag) override;				//  <-- Player Interface


	UPROPERTY(EditDefaultsOnly)
	float DeathTime = 5.0f;

	FTimerHandle DeathTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent> LevelUpNiagaraComponent;

	virtual void OnRep_Stunned() override;
	virtual void OnRep_Burned() override;

	void LoadProgress();

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> PlayerCamera;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> PlayerSpringArm;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> CameraBoxComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> InteractionComponent;

	virtual void InitAbilityActorInfo() override;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastLevelUpParticles() const;

};
