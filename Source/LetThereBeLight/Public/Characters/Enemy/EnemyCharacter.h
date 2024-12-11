// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Characters/Base/BaseCharacter.h"
#include "Interactions/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "EnemyCharacter.generated.h"

class UWidgetComponent;
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
	virtual void UnHighlightActor() override;	// End Enemy Interface

	virtual int32 GetPlayerLevel() override;	// Combat Interface

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	void SetProgressBar();
	void BindAndBroadcastDelegate();
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed = 250.0f;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo () override;
	virtual void InitializeDefaultAttributes() const override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
};