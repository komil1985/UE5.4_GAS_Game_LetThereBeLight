// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 *  KDGameplayTags
 * 
 *  singleton containing native gameplay tags
 */

struct FKDGameplayTags
{
public:
	static const FKDGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
	
	// Primary Tags
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;

	// Secondary Tags
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;

	// Resistance Tags
	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Ice;
	FGameplayTag Attributes_Resistance_Lightning;
	FGameplayTag Attributes_Resistance_Physical;

	// Input Tags
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_Num1;
	FGameplayTag InputTag_Num2;
	FGameplayTag InputTag_Num3;
	FGameplayTag InputTag_Num4;
	
	// Damage Types Tags
	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Ice;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Physical;
	FGameplayTag Damage_Magic;

	// Attack Types Abilities Tags
	FGameplayTag Abilities_Attack;
	FGameplayTag Abilities_Summon;
	FGameplayTag Abilities_Fire_FireBolt;
	FGameplayTag CoolDown_Fire_FireBolt;

	// Combat Socket Tags
	FGameplayTag CombatSocket_Weapon;
	FGameplayTag CombatSocket_RightHand;
	FGameplayTag CombatSocket_LeftHand;

	// Montage Tags
	FGameplayTag Montage_Attack_01;
	FGameplayTag Montage_Attack_02;
	FGameplayTag Montage_Attack_03;
	FGameplayTag Montage_Attack_04;

	// Effect Tags
	FGameplayTag Effect_HitReact;
	FGameplayTag Effect_Die;

	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;

private:
	static FKDGameplayTags GameplayTags;

};