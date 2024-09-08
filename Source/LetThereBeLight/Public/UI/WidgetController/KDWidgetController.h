// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "KDWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API UKDWidgetController : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<class UAttributeSet> AttributeSet;
};
