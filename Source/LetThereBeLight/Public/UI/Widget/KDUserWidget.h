// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KDUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API UKDUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
