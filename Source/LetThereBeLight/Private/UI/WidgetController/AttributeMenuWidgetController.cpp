// Copyright ASKD Games


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/KDAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include <Characters/Player/MyPlayerState.h>


void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UKDAttributeSet* AS = CastChecked<UKDAttributeSet>(AttributeSet);
	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttribute)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			}
		);
	}

	AMyPlayerState* KDPlayerState = Cast<AMyPlayerState>(PlayerState);
	KDPlayerState->OnAttributePointsChangedDelegate.AddLambda(
		[this](int32 Points)
		{
			AttributePointsChangedDelegate.Broadcast(Points);
		}
	);
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UKDAttributeSet* AS = CastChecked<UKDAttributeSet>(AttributeSet);
	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttribute)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}

	AMyPlayerState* KDPlayerState = Cast<AMyPlayerState>(PlayerState);
	AttributePointsChangedDelegate.Broadcast(KDPlayerState->GetAttributePoints());
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FKDAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
