// Copyright ASKD Games


#include "UI/WidgetController/KDWidgetController.h"

void UKDWidgetController::SetWidgetControllerParams(const FWidgetControllerParams WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;

}

void UKDWidgetController::BroadcastInitialValues()
{
}
