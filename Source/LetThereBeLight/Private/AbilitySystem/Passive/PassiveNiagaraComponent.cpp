// Copyright ASKD Games


#include "AbilitySystem/Passive/PassiveNiagaraComponent.h"
#include "AbilitySystem/KDAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Interactions/CombatInterface.h"
#include "Misc/KDGameplayTags.h"


UPassiveNiagaraComponent::UPassiveNiagaraComponent()
{
	bAutoActivate = false;
}

void UPassiveNiagaraComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UKDAbilitySystemComponent* KDASC = Cast<UKDAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner())))
	{
		KDASC->ActivatePassiveEffect.AddUObject(this, &UPassiveNiagaraComponent::OnPassiveActivate);
		ActivateIfEquipped(KDASC);
	}
	else if(ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetOwner()))
	{
		CombatInterface->GetOnASCRegisteredDelegate().AddLambda
		(
			[this] (UAbilitySystemComponent* ASC) 
			{
				if (UKDAbilitySystemComponent* KDASC = Cast<UKDAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner())))
				{
					KDASC->ActivatePassiveEffect.AddUObject(this, &UPassiveNiagaraComponent::OnPassiveActivate);
					ActivateIfEquipped(KDASC);
				}
			}
		);
	}
}

void UPassiveNiagaraComponent::OnPassiveActivate(const FGameplayTag& AbilityTag, bool bActivate)
{
	if (AbilityTag.MatchesTagExact(PassiveSpellTag))
	{
		if (bActivate && !IsActive())
		{
			Activate();
		}
		else
		{
			Deactivate();
		}
	}
}

void UPassiveNiagaraComponent::ActivateIfEquipped(UKDAbilitySystemComponent* KDASC)
{
	const bool bStartupAbilitiesGiven = KDASC->bStartupAbilitiesGiven;
	if (bStartupAbilitiesGiven)
	{
		if (KDASC->GetStatusFromAbilityTag(PassiveSpellTag) == FKDGameplayTags::Get().Abilities_Status_Equipped)
		{
			Activate();
		}
	}
}
