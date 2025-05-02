// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Characters/Base/BaseCharacter.h"
#include "Interactions/EnemyInterface.h"
#include "Interactions/HighLightInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "EnemyCharacter.generated.h"

class UWidgetComponent;
class UBehaviorTree;
class AKDAIController;
/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API AEnemyCharacter : public ABaseCharacter, public IEnemyInterface, public IHighLightInterface
{
	GENERATED_BODY()
public:
	AEnemyCharacter();

	virtual void PossessedBy(AController* NewController) override;

	virtual void HighlightActor_Implementation() override;								// <-- Highlight Interface
	virtual void UnHighlightActor_Implementation() override;							// <-- Highlight Interface
	virtual void SetMoveToLocation_Implementation(FVector& OutDestination) override;	// <-- Highlight Interface

	virtual int32 GetPlayerLevel_Implementation() override;								// <-- Combat Interface
	virtual void Die(const FVector& DeathImpulse) override;								// <-- Combat Interface
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;		// <-- Combat Interface
	virtual AActor* GetCombatTarget_Implementation() const override;					// <-- Combat Interface

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	void SetProgressBar();
	void BindAndBroadcastDelegate();
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	TObjectPtr<AActor> CombatTarget;

	void SetLevel(int32 InLevel) { Level = InLevel; }

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo () override;
	virtual void InitializeDefaultAttributes() const override;
	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AKDAIController> KDAIController;

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnLoot();
};