// Copyright ASKD Games


#include "UI/WidgetController/KDWidgetController.h"
#include "Characters/Player/MyPlayerController.h"
#include "Characters/Player/MyPlayerState.h"
#include "AbilitySystem/KDAbilitySystemComponent.h"
#include "AbilitySystem/KDAttributeSet.h"
#include <AbilitySystem/Data/AbilityInfo.h>

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

void UKDWidgetController::BindCallbacksToDependencies()
{
}

void UKDWidgetController::BroadcastAbilityInfo()
{
	if (!GetKDAbilitySystemComponent()->bStartupAbilitiesGiven) return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda(
		[this](const FGameplayAbilitySpec& AbilitySpec)
		{
			FKDAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(KDAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
			Info.InputTag = KDAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
			Info.StatusTag = KDAbilitySystemComponent->GetStatusFromSpec(AbilitySpec);
			AbilityInfoDelegate.Broadcast(Info);
		}
	);
	GetKDAbilitySystemComponent()->ForEachAbility(BroadcastDelegate);
}

AMyPlayerController* UKDWidgetController::GetKDPlayerController()
{
	if (KDPlayerController == nullptr)
	{
		KDPlayerController = Cast<AMyPlayerController>(PlayerController);
	}
	return KDPlayerController;
}

AMyPlayerState* UKDWidgetController::GetKDPlayerState()
{
	if (KDPlayerState == nullptr)
	{
		KDPlayerState = Cast<AMyPlayerState>(PlayerState);
	}
	return KDPlayerState;
}

UKDAbilitySystemComponent* UKDWidgetController::GetKDAbilitySystemComponent()
{
	if (KDAbilitySystemComponent == nullptr)
	{
		KDAbilitySystemComponent = Cast<UKDAbilitySystemComponent>(AbilitySystemComponent);
	}
	return KDAbilitySystemComponent;
}

UKDAttributeSet* UKDWidgetController::GetKDAttributeSet()
{
	if (KDAttributeSet == nullptr)
	{
		KDAttributeSet = Cast<UKDAttributeSet>(AttributeSet);
	}
	return KDAttributeSet;
}
