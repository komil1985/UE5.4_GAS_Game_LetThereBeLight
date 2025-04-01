// Copyright ASKD Games


#include "AbilitySystem/Abilities/IcyThorn.h"

FString UIcyThorn::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);

	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>ICY THORNS</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Description
			"<Default>Summon a thorn of ice element, causing </>"
			"<Damage>%d</>"
			"<Default> radial damage at the thorn origin.</>"),

			// Values
			Level,
			ManaCost,
			Cooldown,
			ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>ICY THORNS</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Description
			"<Default>Summons %d thorns of ice element, causing </>"
			"<Damage>%d</>"
			"<Default> radial damage at the thorn origin.</>"),

			// Values
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, MaxNumThorns),
			ScaledDamage);
	}
}

FString UIcyThorn::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);

	return FString::Printf(TEXT(
		// Title
		"<Title>NEXT LEVEL</>\n\n"

		// Details
		"<Small>Level: </><Level>%d</>\n"
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		// Description
		"<Default>Summons %d thorns of ice element, causing </>"
		"<Damage>%d</>"
		"<Default> radial damage at the thorn origin.</>"),

		// Values
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, MaxNumThorns),
		ScaledDamage);
}
