// Copyright ASKD Games


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/KDAttributeSet.h"
#include "AbilitySystem/KDAbilitySystemComponent.h"
#include <AbilitySystem/Data/AbilityInfo.h>
#include <Characters/Player/MyPlayerState.h>
#include "AbilitySystem/Data/LevelUpInfo.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UKDAttributeSet* KDAttributeSet = CastChecked<UKDAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(KDAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(KDAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast((KDAttributeSet->GetMana()));
	OnMaxManaChanged.Broadcast(KDAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	AMyPlayerState* KDPlayerState = CastChecked<AMyPlayerState>(PlayerState);
	KDPlayerState->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);

	const UKDAttributeSet* KDAttributeSet = CastChecked<UKDAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(KDAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(KDAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(KDAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(KDAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);
	
	if (UKDAbilitySystemComponent* KDASC = Cast<UKDAbilitySystemComponent>(AbilitySystemComponent))
	{
		if (KDASC->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilities(KDASC);
		}
		else
		{
			KDASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializeStartupAbilities);
		}
			KDASC->EffectAssetTags.AddLambda(
			[this] (const FGameplayTagContainer& AssetTagsContainer)
			{
				for (const FGameplayTag& Tag : AssetTagsContainer)
				{
					// Message.HealthPotion.MatchesTag("Message") will return true, "Message".MatchesTag("Message.HealthPotion") will return false
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				
					if (Tag.MatchesTag(MessageTag))
					{
						const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
						MessageWidgetRowDelegate.Broadcast(*Row);
					}
				}
			}
		);
	}
}

void UOverlayWidgetController::OnInitializeStartupAbilities(UKDAbilitySystemComponent* KDAbilitySystemComponent)
{
	if (!KDAbilitySystemComponent->bStartupAbilitiesGiven) return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda( 
		[this, KDAbilitySystemComponent] (const FGameplayAbilitySpec& AbilitySpec)
		{
			FKDAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(KDAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
			Info.InputTag = KDAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
			AbilityInfoDelegate.Broadcast(Info);
		}
	);
	KDAbilitySystemComponent->ForEachAbility(BroadcastDelegate);
}

void UOverlayWidgetController::OnXPChanged(int32 NewXP) const
{
	const AMyPlayerState* KDPlayerState = CastChecked<AMyPlayerState>(PlayerState);
	const ULevelUpInfo* LevelUpInfo = KDPlayerState->LevelUpInfo;
	checkf(LevelUpInfo, TEXT("Unable to find LevelUpInfo. Please fill out MyPlayerState Blueprint"));

	const int32 Level = LevelUpInfo->FindLevelForXP(NewXP);
	const int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num();

	if (Level <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInformation[Level].LevelUpRequirement;
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInformation[Level - 1].LevelUpRequirement;
		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XpForThisLevel = NewXP - PreviousLevelUpRequirement;
		const float XpBarPercent = static_cast<float>(XpForThisLevel) / static_cast<float>(DeltaLevelRequirement);

		OnXpPercentChangedDelegate.Broadcast(XpBarPercent);
	}

}
