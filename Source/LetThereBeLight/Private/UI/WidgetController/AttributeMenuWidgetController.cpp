// Copyright ASKD Games


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include <AbilitySystem/KDAttributeSet.h>
#include <Misc/KDGameplayTags.h>
#include <AbilitySystem/Data/AttributeInfo.h>


void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{

}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UKDAttributeSet* AS = CastChecked<UKDAttributeSet>(AttributeSet);

	check(AttributeInfo);

	FKDAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FKDGameplayTags::Get().Attributes_Primary_Strength);
	Info.AttributeValue = AS->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
}
