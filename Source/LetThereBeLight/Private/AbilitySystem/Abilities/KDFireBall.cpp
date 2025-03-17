// Copyright ASKD Games


#include "AbilitySystem/Abilities/KDFireBall.h"
#include "AbilitySystem/KDAbilitySystemLibrary.h"
#include "Actors/KDProjectile.h"
#include <Kismet/KismetSystemLibrary.h>


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

	TArray<FRotator> Rotations = UKDAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, ProjectileSpread, NumProjectiles);
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
		Projectile->FinishSpawning(SpawnTransform);
	}


	//const FVector LeftOfSpread = Forward.RotateAngleAxis(-ProjectileSpread / 2.0f, FVector::UpVector);
	//const FVector RightOfSpread = Forward.RotateAngleAxis(ProjectileSpread / 2.0f, FVector::UpVector);
	//
	//
	////NumProjectiles = FMath::Min(MaxNumProjectiles, GetAbilityLevel());

	//if (NumProjectiles > 1)
	//{
	//	const float DeltaSpread = ProjectileSpread / (NumProjectiles - 1);
	//	for (int32 i = 0; i < NumProjectiles; i++)
	//	{
	//		FVector Start = SocketLocation + FVector(0, 0, 10);
	//		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
	//		
	//		UKismetSystemLibrary::DrawDebugArrow
	//		(
	//			GetAvatarActorFromActorInfo(), 
	//			Start, 
	//			Start + Direction * 75.0f, 
	//			1, 
	//			FLinearColor::Red, 
	//			120.0f, 
	//			1
	//		);
	//	}
	//}
	//else
	//{
	//	// Single Projectile
	//	FVector Start = SocketLocation + FVector(0, 0, 5);
	//	UKismetSystemLibrary::DrawDebugArrow
	//	(
	//		GetAvatarActorFromActorInfo(),
	//		Start,
	//		Start + Forward * 75.0f,
	//		1,
	//		FLinearColor::Red,
	//		120.0f,
	//		1
	//	);
	//}

	//UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + Forward * 100.0f, 1, FLinearColor::White, 120.0f, 1);
	//UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + LeftOfSpread * 100.0f, 1, FLinearColor::White, 120.0f, 1);
	//UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + RightOfSpread * 100.0f, 1, FLinearColor::White, 120.0f, 1);
}
