// Copyright ASKD Games


#include "AbilitySystem/Abilities/KDFireBall.h"
#include "AbilitySystem/KDAbilitySystemLibrary.h"
#include "Actors/KDProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"


FString UKDFireBall::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
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
			ScaledDamage);
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
			ScaledDamage);
	}
}

FString UKDFireBall::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
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
		ScaledDamage);
}

void UKDFireBall::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride, AActor* HomingTarget)
{
	//To check if it is on server
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation
	(
		GetAvatarActorFromActorInfo(),
		SocketTag
	);

	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	if (bOverridePitch) Rotation.Pitch = PitchOverride;

	const FVector Forward = Rotation.Vector();
	const int32 EffectNumProjectiles = FMath::Min(NumProjectiles, GetAbilityLevel());
	TArray<FRotator> Rotations = UKDAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, ProjectileSpread, EffectNumProjectiles);
	
	for (FRotator& Rot : Rotations)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rot.Quaternion());

		// Spawning projectile
		AKDProjectile* Projectile = GetWorld()->SpawnActorDeferred<AKDProjectile>
			(
				ProjectileClass,
				SpawnTransform,
				GetOwningActorFromActorInfo(),
				Cast<APawn>(GetOwningActorFromActorInfo()),
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			);

		Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();

		if (HomingTarget && HomingTarget->Implements<UCombatInterface>())
		{
			Projectile->ProjectileMovement->HomingTargetComponent = HomingTarget->GetRootComponent();
		}
		else
		{
			Projectile->HomingTargetSceneComponent = NewObject<USceneComponent>(USceneComponent::StaticClass());
			Projectile->HomingTargetSceneComponent->SetWorldLocation(ProjectileTargetLocation);
			Projectile->ProjectileMovement->HomingTargetComponent = Projectile->HomingTargetSceneComponent;
		}

		Projectile->ProjectileMovement->HomingAccelerationMagnitude = FMath::FRandRange(HomingAccelerationMin, HomingAccelerationMax);
		Projectile->ProjectileMovement->bIsHomingProjectile = bLaunchHomingProjectiles;
		Projectile->FinishSpawning(SpawnTransform);
	}
}
