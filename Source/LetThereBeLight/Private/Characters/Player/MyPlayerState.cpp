// Copyright ASKD Games


#include "Characters/Player/MyPlayerState.h"
#include "AbilitySystem/KDAbilitySystemComponent.h"
#include "AbilitySystem/KDAttributeSet.h"
#include "Net/UnrealNetwork.h"

AMyPlayerState::AMyPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UKDAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UKDAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.0f;
}

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPlayerState, PlayerXP);
	DOREPLIFETIME(AMyPlayerState, PlayerLevel);
	DOREPLIFETIME(AMyPlayerState, AttributePoints);
	DOREPLIFETIME(AMyPlayerState, SpellPoints);
}

UAbilitySystemComponent* AMyPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMyPlayerState::AddToXP(int32 InXP)
{
	PlayerXP += InXP;
	OnXPChangedDelegate.Broadcast(PlayerXP);
}

void AMyPlayerState::AddToLevel(int32 InLevel)
{
	PlayerLevel += InLevel;
	OnLevelChangedDelegate.Broadcast(PlayerLevel, true);
}

void AMyPlayerState::AddAttributePoints(int32 InAttributePoints)
{
	AttributePoints += InAttributePoints;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AMyPlayerState::AddSpellPoints(int32 InSpellPoints)
{
	SpellPoints += InSpellPoints;
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

void AMyPlayerState::SetXP(int32 InXP)
{
	PlayerXP = InXP;
	OnXPChangedDelegate.Broadcast(PlayerXP);
}

void AMyPlayerState::SetLevel(int32 InLevel)
{
	PlayerLevel = InLevel;
	OnLevelChangedDelegate.Broadcast(PlayerLevel, false);
}

void AMyPlayerState::SetAttributePoints(int32 InAttributePoints)
{
	AttributePoints = InAttributePoints;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AMyPlayerState::SetSpellPoints(int32 InSpellPoints)
{
	SpellPoints = InSpellPoints;
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

void AMyPlayerState::OnRep_PlayerXP(int32 OldPlayerXP)
{
	OnXPChangedDelegate.Broadcast(PlayerXP);
}

void AMyPlayerState::OnRep_PlayerLevel(int32 OldPlayerLevel)
{
	OnLevelChangedDelegate.Broadcast(PlayerLevel, true);
}

void AMyPlayerState::OnRep_AttributePoints(int32 OldAttributePoints)
{
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AMyPlayerState::OnRep_SpellPoints(int32 OldSpellPoints)
{
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}
