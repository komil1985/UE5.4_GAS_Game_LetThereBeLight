// Copyright ASKD Games


#include "Misc/KDGameplayTags.h"
#include "GameplayTagsManager.h"

FKDGameplayTags FKDGameplayTags::GameplayTags;

void FKDGameplayTags::InitializeNativeGameplayTags()
{
	// Primary Attributes Tags
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"),
		FString("Increases Physical Damage")
	);
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"),
		FString("Increases Magical Damage")
	);
	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Resilience"),
		FString("Increases Armor And Armor Penetration")
	);
	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"),
		FString("Increases Max Health")
	);

	// Secondary Attributes Tags
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"), 
		FString("Reduces Damage Taken, Improves Block Chance")
	);
	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"),
		FString("Ignored Percentage Of Enemy Armor, Increases Critical Hit Chance")
	);
	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.BlockChance"),
		FString("Chance To Reduce Incoming Damage In Half")
	);
	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitChance"),
		FString("Chance To Double The Damage And Critical Hit Bonus")
	);
	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitDamage"),
		FString("Increases Bonus Damage When Critical Hit Is Triggered")
	);
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitResistance"),
		FString("Chance To Reduce Critical Hit Damage From Enemy")
	);
	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"),
		FString("Increases Amount Of Health Regeneration Every 1 Second")
	);
	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"),
		FString("Increases Amount Of Mana Regeneration Every 1 Second")
	);
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"),
		FString("Increases Maximum Health")
	);
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"),
		FString("Increases Maximum Mana")
	);


	// Input Tags
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("Input Tag For Left Mouse Button")
		);
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("Input Tag For Right Mouse Button")
		);
	GameplayTags.InputTag_Num1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Num1"),
		FString("Input Tag For Number 1 Key")
	);
	GameplayTags.InputTag_Num2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Num2"),
		FString("Input Tag For Number 2 Key")
	);
	GameplayTags.InputTag_Num3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Num3"),
		FString("Input Tag For Number 3 Key")
	);
	GameplayTags.InputTag_Num4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Num4"),
		FString("Input Tag For Number 4 Key")
	);


}
