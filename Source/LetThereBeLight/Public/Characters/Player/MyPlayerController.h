// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <GameplayTagContainer.h>
#include "MyPlayerController.generated.h"

/**
 * 
 */
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class IEnemyInterface;
class UKDInputConfig;
class UKDAbilitySystemComponent;
class USplineComponent;
class UDamageTextComponent;
class UNiagaraSystem;

UCLASS()
class LETTHEREBELIGHT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();
	void subsystem();
	void MouseCursorMode();
	virtual void PlayerTick(float DeltaTime) override;
	
	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool bBlockedHit, bool bCriticalHit);

protected:
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> PlayerContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ShiftAction;

	void ShiftPressed() { bIsShiftKeyDown = true; };
	void ShiftReleased() { bIsShiftKeyDown = false; };
	bool bIsShiftKeyDown = false;
	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();

	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;

	FHitResult CursorHit;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UKDInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UKDAbilitySystemComponent> KDAbilitySystemComponent;

	UKDAbilitySystemComponent* GetKDASC();

	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.0f;
	float ShortPressedThreshold = 0.5f;
	bool bAutoRunning = false;
	float bTargeting = false;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.0f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraSystem> ClickNiagaraSystem;

	void AutoRunning();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
};
