// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KDHUD.generated.h"

class APlayerController;
class APlayerState;
class UAbilitySystemComponent;
class UAttributeSet;
class UKDUserWidget;
class UOverlayWidgetController;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API AKDHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TObjectPtr<UKDUserWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController (const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UKDUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
