// Copyright ASKD Games


#include "Actors/KDProjectileFireBall.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/KDAbilitySystemLibrary.h"
#include "GameplayCueManager.h"
#include "Components/AudioComponent.h"
#include "Misc/KDGameplayTags.h"

void AKDProjectileFireBall::BeginPlay()
{
	Super::BeginPlay();

	StartOutgoingTimeline();
}

void AKDProjectileFireBall::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValidOverlap(OtherActor)) return;

	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			// Calculate And Set Death Impulse
			const FVector DeathImpulse = GetActorForwardVector() * DamageEffectParams.DeathImpulseMagnitude;
			DamageEffectParams.DeathImpulse = DeathImpulse;

			// Applying Damage Effects
			DamageEffectParams.TargetAbilitySystemComponent = TargetASC;
			UKDAbilitySystemLibrary::ApplyDamageEffect(DamageEffectParams);
		}
	}
}

void AKDProjectileFireBall::OnHit()
{
	if (GetOwner())
	{
		FGameplayCueParameters CueParams;
		CueParams.Location = GetActorLocation();
		UGameplayCueManager::ExecuteGameplayCue_NonReplicated(GetOwner(), FKDGameplayTags::Get().GameplayCue_FireBlast, CueParams);
	}

	if (LoopingSoundComponent)
	{
		LoopingSoundComponent->Stop();
		LoopingSoundComponent->DestroyComponent();
	}
	bHit = true;
}
