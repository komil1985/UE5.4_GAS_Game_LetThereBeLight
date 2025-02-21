// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Characters/Base/BaseCharacter.h"
#include "Interactions/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "EnemyCharacter.generated.h"

class UWidgetComponent;
class UBehaviorTree;
class AKDAIController;
/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API AEnemyCharacter : public ABaseCharacter, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AEnemyCharacter();

	virtual void PossessedBy(AController* NewController) override;

	virtual void HighlightActor() override;			//							<-- Enemy Interface
	virtual void UnHighlightActor() override;		//							<--	Enemy Interface

	virtual int32 GetPlayerLevel_Implementation() override;		//							<-- Combat Interface
	virtual void Die() override;					//							<-- Combat Interface
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;	// <-- Combat Interface
	virtual AActor* GetCombatTarget_Implementation() const override;


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
	float BaseWalkSpeed = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	TObjectPtr<AActor> CombatTarget;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo () override;
	virtual void InitializeDefaultAttributes() const override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AKDAIController> KDAIController;
};