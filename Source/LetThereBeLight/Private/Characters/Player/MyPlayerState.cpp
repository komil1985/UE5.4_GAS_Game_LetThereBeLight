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
	OnLevelChangedDelegate.Broadcast(PlayerLevel);
}

void AMyPlayerState::SetXP(int32 InXP)
{
	PlayerXP = InXP;
	OnXPChangedDelegate.Broadcast(PlayerXP);
}

void AMyPlayerState::SetLevel(int32 InLevel)
{
	PlayerLevel = InLevel;
	OnLevelChangedDelegate.Broadcast(PlayerLevel);
}

void AMyPlayerState::OnRep_PlayerXP(int32 OldPlayerXP)
{
	OnXPChangedDelegate.Broadcast(PlayerXP);
}

void AMyPlayerState::OnRep_PlayerLevel(int32 OldPlayerLevel)
{
	OnLevelChangedDelegate.Broadcast(PlayerLevel);
}