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
	GameplayTags.Attributes_Secondary_MaxStamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxStamina"),
		FString("Increases Maximum Stamina")
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
	GameplayTags.InputTag_Passive_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Passive.1"),
		FString("Input Tag For Passive Ability 1")
	);
	GameplayTags.InputTag_Passive_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Passive.2"),
		FString("Input Tag For Passive Ability 2")
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
	GameplayTags.Damage_Magic = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Magic"),
		FString("Damage Type Is Magic")
	);

	// Debuff Types Tags
	GameplayTags.Debuff_Burn = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Burn"),
		FString("Debuff For Fire Damage")
	);
	GameplayTags.Debuff_Freeze = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Freeze"),
		FString("Debuff For Ice Damage")
	);
	GameplayTags.Debuff_Stun = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Stun"),
		FString("Debuff For Lightning Damage")
	);
	GameplayTags.Debuff_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Physical"),
		FString("Debuff For Melee Damage")
	);

	// Debuff Parameter Types Tags
	GameplayTags.Debuff_Chance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Chance"),
		FString("Debuff Chance")
	);
	GameplayTags.Debuff_Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Damage"),
		FString("Debuff Damage")
	);
	GameplayTags.Debuff_Duration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Duration"),
		FString("Debuff Duration")
	);
	GameplayTags.Debuff_Frequency = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Frequency"),
		FString("Debuff Frequency")
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


	// Meta Attributes Tags
	GameplayTags.Attributes_Meta_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Meta.IncomingXP"),
		FString("Meta Attributes Tag For IncomingXP")
	);


	// Abilities Tags
	GameplayTags.Abilities_None = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.None"),
		FString("None Abilities Tag is like nullptr for ability tag")
	);
	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Attack"),
		FString("Attack Ability Tag")
	);
	GameplayTags.Abilities_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Summon"),
		FString("Summon Ability Tag")
	);
	GameplayTags.Abilities_Dash = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Dash"),
		FString("Dash Ability Tag")
	);

	////   Fire Abilities and Cooldown
	GameplayTags.Abilities_Fire_FireBall = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Fire.FireBall"),
		FString("FireBall Ability Tag")
	);
	GameplayTags.CoolDown_Fire_FireBall = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CoolDown.Fire.FireBall"),
		FString("FireBall Cooldown Tag")
	);
	GameplayTags.Abilities_Fire_FireBlast = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Fire.FireBlast"),
		FString("FireBlast Ability Tag")
	);
	GameplayTags.CoolDown_Fire_FireBlast = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CoolDown.Fire.FireBlast"),
		FString("FireBlast Cooldown Tag")
	);

	////   Lightning Abilities and Cooldown
	GameplayTags.Abilities_Lightning_LightningBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Lightning.LightningBolt"),
		FString("LightningBolt Ability Tag")
	);
	GameplayTags.CoolDown_Lightning_LightningBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CoolDown.Lightning.LightningBolt"),
		FString("LightningBolt Cooldown Tag")
	);

	GameplayTags.Abilities_Lightning_LightningBeam = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Lightning.LightningBeam"),
		FString("LightningBeam Ability Tag")
	);
	GameplayTags.CoolDown_Lightning_LightningBeam = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CoolDown.Lightning.LightningBeam"),
		FString("LightningBeam Cooldown Tag")
	);

	////   Ice Abilities and Cooldown
	GameplayTags.Abilities_Ice_IcyThorns = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Ice.IcyThorns"),
		FString("IcyThorns Ability Tag")
	);
	GameplayTags.CoolDown_Ice_IcyThorns = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CoolDown.Ice.IcyThorns"),
		FString("IcyThorns Cooldown Tag")
	);

	////   Passive Ability Tags
	GameplayTags.Abilities_Passive_Halo = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Passive.Halo"),
		FString("Passive Ability Tag Halo")
	);
	GameplayTags.Abilities_Passive_Life = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Passive.Life"),
		FString("Passive Ability Tag Life")
	);
	GameplayTags.Abilities_Passive_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Passive.Mana"),
		FString("Passive Ability Tag Mana")
	);

	////   Extra Ability Tags
	GameplayTags.Abilities_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.HitReact"),
		FString("Hit React Ability Tag")
	);

	////   Ability Status Tags
	GameplayTags.Abilities_Status_Eligible = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Eligible"),
		FString("Eligible Status Ability Tag")
	);
	GameplayTags.Abilities_Status_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Equipped"),
		FString("Equipped Status Ability Tag")
	);
	GameplayTags.Abilities_Status_Locked = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Locked"),
		FString("Locked Status Ability Tag")
	);
	GameplayTags.Abilities_Status_Unlocked = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Unlocked"),
		FString("Unlocked Status Ability Tag")
	);
	GameplayTags.Abilities_Type_Offensive = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Type.Offensive"),
		FString("Offensive Type Ability Tag")
	);
	GameplayTags.Abilities_Type_Passive = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Type.Passive"),
		FString("Passive Type Ability Tag")
	);
	GameplayTags.Abilities_Type_None = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Type.None"),
		FString("None Type Ability Tag")
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

	// Player Block Tags
	GameplayTags.Player_Block_InputPressed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputPressed"),
		FString("Block Input Presesed callback for input")
	);
	GameplayTags.Player_Block_InputHeld = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputHeld"),
		FString("Block Input Held callback for input")
	);
	GameplayTags.Player_Block_InputReleased = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputReleased"),
		FString("Block Input Released callback for input")
	);
	GameplayTags.Player_Block_CursorTrace = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.CursorTrace"),
		FString("Block tracing under cursor")
	);

	// Gameplay Cue Tags
	GameplayTags.GameplayCue_FireBlast = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("GameplayCue.FireBlast"),
		FString("FireBlast Gameplay Cue Tag")
	);

	// Map of damage types to resistances /////////////////////////////////////////////////////////////////////////////////////////////
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Ice, GameplayTags.Attributes_Resistance_Ice);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning, GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_Physical);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// Map of damage types to debuffs     /////////////////////////////////////////////////////////////////////////////////////////////
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Fire, GameplayTags.Debuff_Burn);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Ice, GameplayTags.Debuff_Freeze);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Lightning, GameplayTags.Debuff_Stun);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Physical, GameplayTags.Debuff_Physical);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}