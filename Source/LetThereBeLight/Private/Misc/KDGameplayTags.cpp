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


	// Damage Types Tags
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage"),
		FString("Damage")
	);
	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Fire"),
		FString("Damage Type Is Fire")
	);
	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Lightning"),
		FString("Damage Type Is Lightning")
	);
	GameplayTags.Damage_Ice = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Ice"),
		FString("Damage Type Is Ice")
	);
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Physical"),
		FString("Damage Type Is Physical")
	);


	// Resistance Types Tags
	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Fire"),
		FString("Resistance To Fire Damage")
	);
	GameplayTags.Attributes_Resistance_Ice = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Ice"),
		FString("Resistance To Ice Damage")
	);
	GameplayTags.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Lightning"),
		FString("Resistance To Lightning Damage")
	);
	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Physical"),
		FString("Resistance To Physical Damage")
	);


	// Abilities Tags
	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Attack"),
		FString("Attack Ability Tag")
	);
	GameplayTags.Abilities_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Summon"),
		FString("Summon Ability Tag")
	);


	// Combat Socket Tags
	GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.Weapon"),
		FString("Attack with a Weapon")
	);
	GameplayTags.CombatSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.RightHand"),
		FString("Attack with RightHand")
	);
	GameplayTags.CombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.LeftHand"),
		FString("Attack with LeftHand")
	);

	// Montage Tags
	GameplayTags.Montage_Attack_01 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.01"),
		FString("Attack 01")
	);
	GameplayTags.Montage_Attack_02 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.02"),
		FString("Attack 02")
	);
	GameplayTags.Montage_Attack_03 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.03"),
		FString("Attack 03")
	);
	GameplayTags.Montage_Attack_04 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.04"),
		FString("Attack 04")
	);

	// Effects Tags
	GameplayTags.Effect_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.HitReact"),
		FString("Tag Granted When Hit Reacting")
	);
	GameplayTags.Effect_Die = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Die"),
		FString("Tag Granted When Owner Dies")
	);


	// Map of damage types to resistances /////////////////////////////////////////////////////////////////////////////////////////////
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Ice, GameplayTags.Attributes_Resistance_Ice);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning, GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_Physical);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	 
}