// Copyright ASKD Games


#include "AbilitySystem/Abilities/KDFireBlast.h"
#include "AbilitySystem/KDAbilitySystemLibrary.h"
#include "Actors/KDProjectileFireBall.h"

FString UKDFireBlast::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);

	
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BLAST</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Description
			"<Default>Launches %d </>"
			"<Default>fire balls in all directions, each coming back and </>"
			"<Default>exploding upon return causing </>"
			"<Damage>%d</>"
			"<Default> radial fire damage with a chance to burn</>"),

			// Values
			Level,
			ManaCost,
			Cooldown,
			ScaledDamage);
	
}

FString UKDFireBlast::GetNextLevelDescription(int32 Level)
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
		"<Default>Launches %d </>"
		"<Default>fire balls in all directions, each coming back and </>"
		"<Default>exploding upon return causing </>"
		"<Damage>%d</>"
		"<Default> radial fire damage with a chance to burn</>"),

		// Values
		Level,
		ManaCost,
		Cooldown,
		ScaledDamage);
}

TArray<AKDProjectileFireBall*> UKDFireBlast::SpawnFireBalls()
{
	TArray<AKDProjectileFireBall*> FireBalls;
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	TArray<FRotator> Rotators = UKDAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, 360.0f, NumFireBalls);

	for (const FRotator& Rotator : Rotators)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Location);
		SpawnTransform.SetRotation(Rotator.Quaternion());

		AKDProjectileFireBall* FireBall = GetWorld()->SpawnActorDeferred<AKDProjectileFireBall>
			(
				ProjectileFireBallClass,
				SpawnTransform,
				GetOwningActorFromActorInfo(),
				CurrentActorInfo->PlayerController->GetPawn(),
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			);

		FireBall->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
		FireBall->ReturnToActor = GetAvatarActorFromActorInfo();

		FireBalls.Add(FireBall);

		FireBall->FinishSpawning(SpawnTransform);
	}

	return FireBalls;

}
