// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/KDWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API UAttributeMenuWidgetController : public UKDWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;
};
