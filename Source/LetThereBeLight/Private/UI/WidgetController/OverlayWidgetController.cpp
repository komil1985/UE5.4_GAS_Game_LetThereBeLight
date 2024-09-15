// Copyright ASKD Games


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/KDAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UKDAttributeSet* KDAttributeSet = CastChecked<UKDAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(KDAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(KDAttributeSet->GetMaxHealth());
}
