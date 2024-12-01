// Copyright ASKD Games


#include "AbilitySystem/Abilities/KDProjectileSpell.h"
#include "Actors/KDProjectile.h"
#include "Interactions/CombatInterface.h"


void UKDProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	//UKismetSystemLibrary::PrintString(this, FString("ActivateAbility (C++)"), true, true, FLinearColor::Green, 3.0f);//
}

void UKDProjectileSpell::SpawnProjectile()
{
	//To check if it is on server
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	// Spawning projectile
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);

		AKDProjectile* Projectile = GetWorld()->SpawnActorDeferred<AKDProjectile>
			(
				ProjectileClass,
				SpawnTransform,
				GetOwningActorFromActorInfo(),
				Cast<APawn>(GetOwningActorFromActorInfo()),
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			);
		Projectile->FinishSpawning(SpawnTransform);
	}
}
