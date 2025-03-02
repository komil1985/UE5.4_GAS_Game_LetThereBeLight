// Copyright ASKD Games


#include "UI/WidgetController/SpellMenuWidgetController.h"
#include "AbilitySystem/KDAbilitySystemComponent.h"
#include "Characters/Player/MyPlayerState.h"
#include "AbilitySystem/Data/AbilityInfo.h"

void USpellMenuWidgetController::BroadcastInitialValues()
{
	BroadcastAbilityInfo();
	SpellPointChanged.Broadcast(GetKDPlayerState()->GetSpellPoints());
}

void USpellMenuWidgetController::BindCallbacksToDependencies()
{
	GetKDAbilitySystemComponent()->AbilityStatusChanged.AddLambda(
		[this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag)
		{
			if (AbilityInfo)
			{
				FKDAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
				Info.StatusTag = StatusTag;
				AbilityInfoDelegate.Broadcast(Info);
			}
		}
	);

	GetKDPlayerState()->OnSpellPointsChangedDelegate.AddLambda(
		[this](int32 SpellPoints)
		{
			SpellPointChanged.Broadcast(SpellPoints);
		}
	);
}
