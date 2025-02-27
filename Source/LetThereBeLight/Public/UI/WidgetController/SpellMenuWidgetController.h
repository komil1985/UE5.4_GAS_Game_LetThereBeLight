// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/KDWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API USpellMenuWidgetController : public UKDWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
};
