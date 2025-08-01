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
	FGameplayTag Attributes_Secondary_MaxStamina;

	// Meta Tags
	FGameplayTag Attributes_Meta_IncomingXP;

	// Input Tags
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_Spacebar;
	FGameplayTag InputTag_Num1;
	FGameplayTag InputTag_Num2;
	FGameplayTag InputTag_Num3;
	FGameplayTag InputTag_Num4;
	FGameplayTag InputTag_Passive_1;
	FGameplayTag InputTag_Passive_2;
	
	// Damage Types Tags
	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Ice;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Physical;
	FGameplayTag Damage_Magic;

	// Debuff Tags
	FGameplayTag Debuff_Burn;
	FGameplayTag Debuff_Freeze;
	FGameplayTag Debuff_Stun;
	FGameplayTag Debuff_Physical;

	// Debuff Paramater Tags
	FGameplayTag Debuff_Chance;
	FGameplayTag Debuff_Damage;
	FGameplayTag Debuff_Duration;
	FGameplayTag Debuff_Frequency;

	// Resistance Tags
	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Ice;
	FGameplayTag Attributes_Resistance_Lightning;
	FGameplayTag Attributes_Resistance_Physical;

	// Attack Types Abilities Tags
	FGameplayTag Abilities_None;
	FGameplayTag Abilities_Attack;
	FGameplayTag Abilities_Summon;
	FGameplayTag Abilities_HitReact;
	FGameplayTag Abilities_Dash;
	
	// Status Type Abilities Tag
	FGameplayTag Abilities_Status_Eligible;
	FGameplayTag Abilities_Status_Equipped;
	FGameplayTag Abilities_Status_Locked;
	FGameplayTag Abilities_Status_Unlocked;

	// 
	FGameplayTag Abilities_Type_Defensive;
	FGameplayTag Abilities_Type_Offensive;
	FGameplayTag Abilities_Type_Passive;
	FGameplayTag Abilities_Type_None;

	// Offensive Skills Ability Tags
	FGameplayTag Abilities_Fire_FireBall;
	FGameplayTag Abilities_Fire_FireBlast;
	FGameplayTag Abilities_Lightning_LightningBolt;
	FGameplayTag Abilities_Lightning_LightningBeam;
	FGameplayTag Abilities_Ice_IcyThorns;

	// Skills Cooldown Ability Tags
	FGameplayTag CoolDown_Fire_FireBall;
	FGameplayTag CoolDown_Fire_FireBlast;
	FGameplayTag CoolDown_Lightning_LightningBolt;
	FGameplayTag CoolDown_Lightning_LightningBeam;
	FGameplayTag CoolDown_Ice_IcyThorns;
	FGameplayTag CoolDown_Ability_Dash;

	// Passive Ability Tags
	FGameplayTag Abilities_Passive_Halo;
	FGameplayTag Abilities_Passive_Life;
	FGameplayTag Abilities_Passive_Mana;

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
	
	// Player Block Tags
	FGameplayTag Player_Block_InputPressed;
	FGameplayTag Player_Block_InputHeld;
	FGameplayTag Player_Block_InputReleased;
	FGameplayTag Player_Block_CursorTrace;

	// Gameplay Cues
	FGameplayTag GameplayCue_FireBlast;

	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;
	TMap<FGameplayTag, FGameplayTag> DamageTypesToDebuffs;

private:
	static FKDGameplayTags GameplayTags;

};