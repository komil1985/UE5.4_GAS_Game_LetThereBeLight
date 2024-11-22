// Copyright ASKD Games


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/KDAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"


void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UKDAttributeSet* AS = CastChecked<UKDAttributeSet>(AttributeSet);

	for (auto& Pair : AS->TagsToAttribute)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair, AS](const FOnAttributeChangeData& Data)
			{
				FKDAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
				Info.AttributeValue = Pair.Value().GetNumericValue(AS);
				AttributeInfoDelegate.Broadcast(Info);
			}
		);
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UKDAttributeSet* AS = CastChecked<UKDAttributeSet>(AttributeSet);

	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttribute)
	{
		//BroadcastAttributeInfo(Pair.Key, Pair.Value());

		FKDAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);
	}
}

//void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
//{
//	FKDAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
//	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
//	AttributeInfoDelegate.Broadcast(Info);
//}
