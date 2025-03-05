// Copyright ASKD Games


#include "AbilitySystem/Abilities/KDFireBall.h"
#include "Misc/KDGameplayTags.h"


FString UKDFireBall::GetDescription(int32 Level)
{
	const int32 Damage = GetDamageByDamageType(Level, FKDGameplayTags::Get().Damage_Fire);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);

	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BALL</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Description
			"<Default>Launches a fire ball exploding on impact, dealing </>"
			"<Damage>%d</>"
			"<Default> fire damage with a chance to burn</>"),

			// Values
			Level, 
			ManaCost,
			Cooldown,
			Damage);
	}
	else
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BALL</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Description
			"<Default>Launches %d fire ball exploding on impact dealing </>"
			"<Damage>%d</>"
			"<Default> fire damage with a chance to burn</>"),

			// Values
			Level, 
			ManaCost,
			Cooldown,
			FMath::Min(Level, NumProjectiles), 
			Damage);
	}
}
FString UKDFireBall::GetNextLevelDescription(int32 Level)
{
	const int32 Damage = GetDamageByDamageType(Level, FKDGameplayTags::Get().Damage_Fire);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);

	return FString::Printf(TEXT(
		// Title
		"<Title>NEXT LEVEL </>\n\n"

		// Details
		"<Small>Level: </><Level>%d</>\n"
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		//Description
		"<Default>Launches %d fire ball exploding on impact dealing </>"
		"<Damage>%d</>"
		"<Default> fire damage with a chance to burn</>"),

		// Values
		Level, 
		ManaCost,
		Cooldown,
		FMath::Min(Level, NumProjectiles), 
		Damage);
}