// Copyright ASKD Games


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/KDAttributeSet.h"
#include "AbilitySystem/KDAbilitySystemComponent.h"


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
			OnInitilizeStartupAbilities(KDASC);
		}
		else
		{
			KDASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitilizeStartupAbilities);
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

void UOverlayWidgetController::OnInitilizeStartupAbilities(UKDAbilitySystemComponent* KDAbilitySystemComponent)
{
	if (!KDAbilitySystemComponent->bStartupAbilitiesGiven) return;
}
