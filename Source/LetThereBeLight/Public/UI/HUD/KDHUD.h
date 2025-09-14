// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KDHUD.generated.h"

class UAttributeMenuWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
class UKDUserWidget;
class UOverlayWidgetController;
struct FWidgetControllerParams;
class USpellMenuWidgetController;
/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API AKDHUD : public AHUD
{
	GENERATED_BODY()
public:

	UOverlayWidgetController* GetOverlayWidgetController (const FWidgetControllerParams& WCParams);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController (const FWidgetControllerParams& WCParams);
	USpellMenuWidgetController* GetSpellMenuWidgetController (const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UUserWidget> BaseWBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> BaseWBPClass;

private:

	UPROPERTY()
	TObjectPtr<UKDUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UKDUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<USpellMenuWidgetController> SpellMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USpellMenuWidgetController> SpellMenuWidgetControllerClass;


};
