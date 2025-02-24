// Copyright ASKD Games


#include "Actors/KDProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraSystem.h"
#include <NiagaraFunctionLibrary.h>
#include "Components/AudioComponent.h"
#include <LetThereBeLight/LetThereBeLight.h>
#include "AbilitySystemComponent.h"
#include <AbilitySystemBlueprintLibrary.h>
#include <AbilitySystem/KDAbilitySystemLibrary.h>

AKDProjectile::AKDProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	SphereComp();
	ProjectileMoveComp();
}

void AKDProjectile::SphereComp()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AKDProjectile::ProjectileMoveComp()
{
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 500.0f;
	ProjectileMovement->MaxSpeed = 500.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
}

void AKDProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LifeSpan);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AKDProjectile::OnSphereOverlap);

	LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());
}

void AKDProjectile::Destroyed()
{
	if (!bHit && !HasAuthority())
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ImpactEffect,GetActorLocation(),FRotator::ZeroRotator);
		if (LoopingSoundComponent) LoopingSoundComponent->Stop();
		bHit = true;
	}
	Super::Destroyed();
}

void AKDProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!DamageEffectSpecHandle.Data.IsValid() || DamageEffectSpecHandle.Data.Get()->GetContext().GetEffectCauser() == OtherActor)
	{
		return;
	}

	if (!UKDAbilitySystemLibrary::IsNotFriend(DamageEffectSpecHandle.Data.Get()->GetContext().GetEffectCauser(), OtherActor))
	{
		return;
	}

	if (!bHit)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation(), FRotator::ZeroRotator);
		if (LoopingSoundComponent) LoopingSoundComponent->Stop();
		bHit = true;
	}

	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		}
		Destroy();
	}
	else
	{
		bHit = true;
	}
}
