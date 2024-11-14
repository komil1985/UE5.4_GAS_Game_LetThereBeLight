// Copyright ASKD Games


#include "AbilitySystem/KDAbilitySystemComponent.h"
#include "Misc/KDGameplayTags.h"

void UKDAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UKDAbilitySystemComponent::EffectApplied);

	const FKDGameplayTags& GameplayTags = FKDGameplayTags::Get();

	//GameplayTags.Attributes_Secondary_Armor.ToString();
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Secondary_Armor.ToString()));
}

void UKDAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);

}
