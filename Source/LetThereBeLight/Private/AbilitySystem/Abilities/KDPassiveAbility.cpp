// Copyright ASKD Games


#include "AbilitySystem/Abilities/KDPassiveAbility.h"
#include "KDPassiveAbility.h"
#include "AbilitySystem/KDAbilitySystemComponent.h"
#include"AbilitySystemBlueprintLibrary.h"

void UKDPassiveAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (UKDAbilitySystemComponent* KDASC = Cast<UKDAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo())))
	{
		KDASC->DeactivatePassiveAbility.AddUObject(this, &UKDPassiveAbility::ReceiveDeactivate);
	}

}

void UKDPassiveAbility::ReceiveDeactivate(const FGameplayTag& AbilityTag)
{
	if (AbilityTags.HasTagExact(AbilityTag))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}
