// Copyright ASKD Games


#include "UI/WidgetController/SpellMenuWidgetController.h"
#include "AbilitySystem/KDAbilitySystemComponent.h"
#include "Characters/Player/MyPlayerState.h"
#include "AbilitySystem/Data/AbilityInfo.h"
//#include "Misc/KDGameplayTags.h"

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
			if (SelectedAbility.Ability.MatchesTagExact(AbilityTag))
			{
				SelectedAbility.Status = StatusTag;
				bool bEnableSpendpoints = false;
				bool bEnableEquip = false;
				ShouldEnableButton(StatusTag, CurrentSpellPoints, bEnableSpendpoints, bEnableEquip);
				SpellGlobeSelectedDelegate.Broadcast(bEnableSpendpoints, bEnableEquip);
			}

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
			CurrentSpellPoints = SpellPoints;
			
			bool bEnableSpendpoints = false;
			bool bEnableEquip = false;
			ShouldEnableButton(SelectedAbility.Status, CurrentSpellPoints, bEnableSpendpoints, bEnableEquip);
			SpellGlobeSelectedDelegate.Broadcast(bEnableSpendpoints, bEnableEquip);
		}
	);
}

void USpellMenuWidgetController::SpellGlobeSelected(const FGameplayTag& AbilityTag)
{
	FGameplayTag AbilityStatus;
	const FKDGameplayTags GameplayTags = FKDGameplayTags::Get();
	const int32 SpellPoints = GetKDPlayerState()->GetSpellPoints();
	const FGameplayAbilitySpec* AbilitySpec = GetKDAbilitySystemComponent()->GetSpecFromAbilityTag(AbilityTag);
	const bool bTagValid = AbilityTag.IsValid();
	const bool bTagNone = AbilityTag.MatchesTag(GameplayTags.Abilities_None);
	const bool bSpecValid = AbilitySpec != nullptr;

	if (!bTagValid || bTagNone || !bSpecValid)
	{
		AbilityStatus = GameplayTags.Abilities_Status_Locked;
	}
	else
	{
		AbilityStatus = GetKDAbilitySystemComponent()->GetStatusFromSpec(*AbilitySpec);
	}

	SelectedAbility.Ability = AbilityTag;
	SelectedAbility.Status = AbilityStatus;

	bool bEnableSpendpoints = false;
	bool bEnableEquip = false;
	ShouldEnableButton(AbilityStatus, SpellPoints, bEnableSpendpoints, bEnableEquip);
	SpellGlobeSelectedDelegate.Broadcast(bEnableSpendpoints, bEnableEquip);
}

void USpellMenuWidgetController::ShouldEnableButton(const FGameplayTag& AbilityStatus, int32 SpellPoints, bool& bShouldEnableSpellPointsButton, bool& bShouldEnableEquipButton)
{
	const FKDGameplayTags GameplayTags = FKDGameplayTags::Get();
	bShouldEnableSpellPointsButton = false;
	bShouldEnableEquipButton = false;

	if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Equipped))
	{
		bShouldEnableEquipButton = true;
		if (SpellPoints > 0)
		{
			bShouldEnableSpellPointsButton = true;
		}
	}
	else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Eligible))
	{
		if (SpellPoints > 0)
		{
			bShouldEnableSpellPointsButton = true;
		}
	}
	else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked))
	{
		bShouldEnableEquipButton = true;
		if (SpellPoints > 0)
		{
			bShouldEnableSpellPointsButton = true;
		}
	}
}