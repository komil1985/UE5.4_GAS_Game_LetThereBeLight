// Copyright ASKD Games


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/KDAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UKDAttributeSet* KDAttributeSet = CastChecked<UKDAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(KDAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(KDAttributeSet->GetMaxHealth());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UKDAttributeSet* KDAttributeSet = CastChecked<UKDAttributeSet>(AttributeSet);


	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		KDAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);


	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		KDAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}


