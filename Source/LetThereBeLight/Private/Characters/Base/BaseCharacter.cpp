// Copyright ASKD Games


#include "Characters/Base/BaseCharacter.h"
#include "AbilitySystem/KDAbilitySystemComponent.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystem/Debuff/DebuffNiagaraComponent.h"
#include <LetThereBeLight/LetThereBeLight.h>
#include <Misc/KDGameplayTags.h>
#include <Kismet/GameplayStatics.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/Passive/PassiveNiagaraComponent.h"
#include "Net/UnrealNetwork.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	const FKDGameplayTags& GameplayTags = FKDGameplayTags::Get();

	BurnDebuffComponent = CreateDefaultSubobject<UDebuffNiagaraComponent>(TEXT("BurnDebuffComponent"));
	BurnDebuffComponent->SetupAttachment(GetRootComponent());
	BurnDebuffComponent->DebuffTag = GameplayTags.Debuff_Burn;

	StunDebuffComponent = CreateDefaultSubobject<UDebuffNiagaraComponent>(TEXT("StunDebuffComponent"));
	StunDebuffComponent->SetupAttachment(GetRootComponent());
	StunDebuffComponent->DebuffTag = GameplayTags.Debuff_Stun;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);

	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), FName("WeaponSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	EffectAttachComponent = CreateDefaultSubobject<USceneComponent>(TEXT("EffectAttachPoint"));
	EffectAttachComponent->SetupAttachment(GetRootComponent());

	HaloSkillNiagaraComponent = CreateDefaultSubobject<UPassiveNiagaraComponent>(TEXT("HaloSkillNiagaraComponent"));
	HaloSkillNiagaraComponent->SetupAttachment(EffectAttachComponent);

	LifeSkillNiagaraComponent = CreateDefaultSubobject<UPassiveNiagaraComponent>(TEXT("LifeSkillNiagaraComponent"));
	LifeSkillNiagaraComponent->SetupAttachment(EffectAttachComponent);

	ManaSkillNiagaraComponent = CreateDefaultSubobject<UPassiveNiagaraComponent>(TEXT("ManaSkillNiagaraComponent"));
	ManaSkillNiagaraComponent->SetupAttachment(EffectAttachComponent);

}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EffectAttachComponent->SetWorldRotation(FRotator::ZeroRotator);
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseCharacter, bIsStunned);
	DOREPLIFETIME(ABaseCharacter, bIsBurned);
	DOREPLIFETIME(ABaseCharacter, bIsBeingShocked);
}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	OnDamageDelegate.Broadcast(DamageTaken);
	return DamageTaken;
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAnimMontage* ABaseCharacter::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void ABaseCharacter::Die(const FVector& DeathImpulse)
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandleDeath(DeathImpulse);	
}

void ABaseCharacter::MulticastHandleDeath_Implementation(const FVector& DeathImpulse)
{
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());

	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Weapon->AddImpulse(DeathImpulse * 0.1f, NAME_None, true);

	GetMesh()->SetSimulatePhysics(false);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	//GetMesh()->AddImpulse(DeathImpulse, NAME_None, true);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Dissolve();
	bDead = true;
	BurnDebuffComponent->Deactivate();
	StunDebuffComponent->Deactivate();
	OnDeathDelegate.Broadcast(this);
}

void ABaseCharacter::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bIsStunned = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bIsStunned ? 0.0f : BaseWalkSpeed;
}


void ABaseCharacter::OnRep_Stunned() {}

void ABaseCharacter::OnRep_Burned() {}


void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector ABaseCharacter::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	const FKDGameplayTags& GameplayTags = FKDGameplayTags::Get();
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_Weapon) && IsValid(Weapon))
	{	
		return Weapon->GetSocketLocation(WeaponTipSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_RightHand))
	{
		return GetMesh()->GetSocketLocation(RightHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_LeftHand))
	{
		return GetMesh()->GetSocketLocation(LeftHandSocketName);
	}
	return FVector();
}

bool ABaseCharacter::IsDead_Implementation() const
{
	return bDead;
}

AActor* ABaseCharacter::GetAvatar_Implementation()
{
	return this;
}

TArray<FTaggedMontage> ABaseCharacter::GetAttackMontages_Implementation()
{
	return AttackMontages;
}

FTaggedMontage ABaseCharacter::GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag)
{
	for (FTaggedMontage TaggedMontage : AttackMontages)
	{
		if (TaggedMontage.MontageTag == MontageTag)
		{
			return TaggedMontage;
		}
	}
	return FTaggedMontage();
}

UNiagaraSystem* ABaseCharacter::GetBloodEffect_Implementation()
{
	return BloodEffect;
}

int32 ABaseCharacter::GetMinionCount_Implementation()
{
	return MinionCount;
}

void ABaseCharacter::IncreaseMinionCount_Implementation(int32 Amount)
{
	MinionCount += Amount;
}

void ABaseCharacter::DecreaseMinionCount_Implementation(int32 Amount)
{
	MinionCount -= Amount;
}

ECharacterClass ABaseCharacter::GetCharacterClass_Implementation()
{
	return CharacterClass;
}

FOnASCRegistered& ABaseCharacter::GetOnASCRegisteredDelegate()
{
	return OnAscRegistered;
}

FOnDeathSignature& ABaseCharacter::GetOnDeathDelegate()
{
	return OnDeathDelegate;
}

FOnDamageSignature& ABaseCharacter::GetOnDamageDelegate()
{
	return OnDamageDelegate;
}

USkeletalMeshComponent* ABaseCharacter::GetWeapon_Implementation()
{
	return Weapon;
}

void ABaseCharacter::SetIsBeingShocked_Implementation(bool bInShock)
{
	bIsBeingShocked = bInShock;
}

bool ABaseCharacter::IsBeingShocked_Implementation() const
{
	return bIsBeingShocked;
}


void ABaseCharacter::InitAbilityActorInfo() {}


void ABaseCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ABaseCharacter::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.0f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.0f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.0f);
}

void ABaseCharacter::AddCharacterAbilities()
{
	UKDAbilitySystemComponent* KDASC = Cast<UKDAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	KDASC->AddCharacterAbilities(StartupAbilities);
	KDASC->AddCharacterPassiveAbilities(StartupPassiveAbilities);
}
void ABaseCharacter::Dissolve()
{
	if (IsValid(MeshDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(MeshDissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicMatInst);
		StartMeshDissolveTimeline(DynamicMatInst);
	}
	if (IsValid(WeaponDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
		Weapon->SetMaterial(0, DynamicMatInst);
		StartWeaponDissolveTimeline(DynamicMatInst);
	}
}

