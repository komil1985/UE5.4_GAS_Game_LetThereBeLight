// Copyright ASKD Games


#include "AbilitySystem/Abilities/KDGameplayAbility.h"

FString UKDGameplayAbility::GetDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>%s, </><Level>%d</>"), L"Default Ability Name - Sample Text Sample Text Sample Text Sample Text Sample Text Sample Text Sample Text Sample Text Sample Text Sample Text.", Level);
}

FString UKDGameplayAbility::GetNextLevelDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>Next Level : </><Level>%d</> \n<Default>Causes more damage </>"), Level);
}

FString UKDGameplayAbility::GetLockedDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>Spell Locked Until Level : %d</>"), Level);
}
