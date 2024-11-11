// Copyright ASKD Games


#include "Misc/KDGameplayTags.h"
#include "GameplayTagsManager.h"

FKDGameplayTags FKDGameplayTags::GameplayTags;

void FKDGameplayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces Damage Taken, Improves Block Chance"));
}
