// Copyright ASKD Games


#include "Misc/KDGameplayTags.h"
#include "GameplayTagsManager.h"

FKDGameplayTags FKDGameplayTags::GameplayTags;

void FKDGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces Damage Taken, Improves Block Chance"));
}
