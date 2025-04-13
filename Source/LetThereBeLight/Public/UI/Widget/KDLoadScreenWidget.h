// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KDLoadScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API UKDLoadScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BlueprintInitializeWidget();
	
};
