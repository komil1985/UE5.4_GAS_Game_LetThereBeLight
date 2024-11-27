// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <GameplayTagContainer.h>
#include "MyPlayerController.generated.h"

/**
 * 
 */
class UInputMappingContext;
struct FInputActionValue;
class UInputAction;
class IEnemyInterface;
class UKDInputConfig;
class UKDAbilitySystemComponent;

UCLASS()
class LETTHEREBELIGHT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();
	void subsystem();
	void MouseCursorMode();
	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> PlayerContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();

	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UKDInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UKDAbilitySystemComponent> KDAbilitySystemComponent;

	UKDAbilitySystemComponent* GetKDASC();
};
