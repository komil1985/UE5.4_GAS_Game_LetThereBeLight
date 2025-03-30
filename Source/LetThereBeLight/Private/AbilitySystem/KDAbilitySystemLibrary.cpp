// Copyright ASKD Games


#include "AbilitySystem/KDAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/Player/MyPlayerState.h"
#include <UI/HUD/KDHUD.h>
#include "UI/WidgetController/KDWidgetController.h"
#include <GameMode/MyGameModeBase.h>
#include <AbilitySystemComponent.h>
#include "Abilities/GameplayAbility.h"
#include <KDAbilityTypes.h>
#include <Interactions/CombatInterface.h>
#include "Engine/OverlapResult.h"
#include <Misc/KDGameplayTags.h>
#include <AbilitySystemBlueprintLibrary.h>

bool UKDAbilitySystemLibrary::MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWCParams, AKDHUD*& OutKDHUD)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		OutKDHUD = Cast<AKDHUD>(PC->GetHUD());
		if (OutKDHUD)
		{
			AMyPlayerState* PS = PC->GetPlayerState<AMyPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			OutWCParams.PlayerController = PC;
			OutWCParams.PlayerState = PS;
			OutWCParams.AbilitySystemComponent = ASC;
			OutWCParams.AttributeSet = AS;

			return true;
		}
	}
	return false;
}

UOverlayWidgetController* UKDAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
	AKDHUD* KDHUD = nullptr;

	if (MakeWidgetControllerParams(WorldContextObject, WCParams, KDHUD))
	{
		return KDHUD->GetOverlayWidgetController(WCParams);
	}

	return nullptr;
}

UAttributeMenuWidgetController* UKDAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
	AKDHUD* KDHUD = nullptr;

	if (MakeWidgetControllerParams(WorldContextObject, WCParams, KDHUD))
	{
		return KDHUD->GetAttributeMenuWidgetController(WCParams);
	}
	return nullptr;
}

USpellMenuWidgetController* UKDAbilitySystemLibrary::GetSpellMenuWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
	AKDHUD* KDHUD = nullptr;

	if (MakeWidgetControllerParams(WorldContextObject, WCParams, KDHUD))
	{
		return KDHUD->GetSpellMenuWidgetController(WCParams);
	}
	return nullptr;
}

void UKDAbilitySystemLibrary::InitilizeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AActor* AvatarActor = ASC->GetAvatarActor();

	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryAttributeContextHandle = ASC->MakeEffectContext();
	PrimaryAttributeContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributeSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributeSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributeContextHandle = ASC->MakeEffectContext();
	SecondaryAttributeContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributeSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributeSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributeContextHandle = ASC->MakeEffectContext();
	VitalAttributeContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributeSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributeSpecHandle.Data.Get());
}

void UKDAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo == nullptr) return;

	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
	const FCharacterClassDefaultInfo& DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultInfo.StartupAbilities)
	{
		if (ASC->GetAvatarActor()->Implements<UCombatInterface>())
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, ICombatInterface::Execute_GetPlayerLevel(ASC->GetAvatarActor()));
			ASC->GiveAbility(AbilitySpec);
		}
	}
}

int32 UKDAbilitySystemLibrary::GetXPRewardForClassAndLevel(const UObject* WorldContextObject, ECharacterClass CharacterClass, int32 CharacterLevel)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo == nullptr) return 0;

	const FCharacterClassDefaultInfo& Info = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	const float XPReward = Info.XPReward.GetValueAtLevel(CharacterLevel);

	return static_cast<int32>(XPReward);
}


UCharacterClassInfo* UKDAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	const AMyGameModeBase* MyGameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (MyGameMode == nullptr) return nullptr;

	return MyGameMode->CharacterClassInfo;
}

UAbilityInfo* UKDAbilitySystemLibrary::GetAbilityInfo(const UObject* WorldContextObject)
{
	const AMyGameModeBase* MyGameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (MyGameMode == nullptr) return nullptr;
	
	return MyGameMode->AbilityInfo;
}

bool UKDAbilitySystemLibrary::IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FKDGameplayEffectContext* KDEffectContext = static_cast<const FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return KDEffectContext->IsSuccessfulDebuff();
	}
	return false;
}

float UKDAbilitySystemLibrary::GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FKDGameplayEffectContext* KDEffectContext = static_cast<const FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return KDEffectContext->GetDebuffDamage();
	}
	return 0.0f;
}

float UKDAbilitySystemLibrary::GetDebuffDuration(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FKDGameplayEffectContext* KDEffectContext = static_cast<const FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return KDEffectContext->GetDebuffDuration();
	}
	return 0.0f;
}

float UKDAbilitySystemLibrary::GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FKDGameplayEffectContext* KDEffectContext = static_cast<const FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return KDEffectContext->GetDebuffFrequency();
	}
	return 0.0f;
}

FGameplayTag UKDAbilitySystemLibrary::GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FKDGameplayEffectContext* KDEffectContext = static_cast<const FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		if (KDEffectContext->GetDamageType().IsValid())
		{
			return *KDEffectContext->GetDamageType();
		}
	}
	return FGameplayTag();
}

FVector UKDAbilitySystemLibrary::GetDeathImpulse(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FKDGameplayEffectContext* KDEffectContext = static_cast<const FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return KDEffectContext->GetDeathImpulse();
	}
	return FVector::ZeroVector;
}

FVector UKDAbilitySystemLibrary::GetKnockbackForce(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FKDGameplayEffectContext* KDEffectContext = static_cast<const FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return KDEffectContext->GetKnockBackForce();
	}
	return FVector::ZeroVector;
}

bool UKDAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FKDGameplayEffectContext* KDEffectContext = static_cast<const FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return KDEffectContext->IsBlockedHit();
	}
	return false;
}

bool UKDAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FKDGameplayEffectContext* KDEffectContext = static_cast<const FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return KDEffectContext->IsCriticalHit();
	}
	return false;
}

bool UKDAbilitySystemLibrary::IsRadialDamage(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FKDGameplayEffectContext* KDEffectContext = static_cast<const FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return KDEffectContext->IsRadialDamage();
	}
	return false;
}

float UKDAbilitySystemLibrary::GetRadialDamageInnerRadius(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FKDGameplayEffectContext* KDEffectContext = static_cast<const FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return KDEffectContext->GetRadialDamageInnerRadius();
	}
	return 0.0f;
}

float UKDAbilitySystemLibrary::GetRadialDamageOuterRadius(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FKDGameplayEffectContext* KDEffectContext = static_cast<const FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return KDEffectContext->GetRadialDamageOuterRadius();
	}
	return 0.0f;
}

FVector UKDAbilitySystemLibrary::GetRadialDamageOrigin(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FKDGameplayEffectContext* KDEffectContext = static_cast<const FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return KDEffectContext->GetRadialDamageOrigin();
	}
	return FVector::ZeroVector;
}

void UKDAbilitySystemLibrary::SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit)
{
	if (FKDGameplayEffectContext* KDEffectContext = static_cast<FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		KDEffectContext->SetIsBlockedHit(bInIsBlockedHit);
	}
}

void UKDAbilitySystemLibrary::SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit)
{
	if (FKDGameplayEffectContext* KDEffectContext = static_cast<FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		KDEffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}

void UKDAbilitySystemLibrary::SetIsSuccessfulDebuff(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, bool bInSuccessfulDebuff)
{
	if (FKDGameplayEffectContext* KDEffectContext = static_cast<FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		KDEffectContext->SetIsSuccessfulDebuff(bInSuccessfulDebuff);
	}
}

void UKDAbilitySystemLibrary::SetDebuffDamage(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, float bInDamage)
{
	if (FKDGameplayEffectContext* KDEffectContext = static_cast<FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		KDEffectContext->SetDebuffDamage(bInDamage);
	}
}

void UKDAbilitySystemLibrary::SetDebuffDuration(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, float bInDuration)
{
	if (FKDGameplayEffectContext* KDEffectContext = static_cast<FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		KDEffectContext->SetDebuffDuration(bInDuration);
	}
}

void UKDAbilitySystemLibrary::SetDebuffFrequency(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, float bInFrequency)
{
	if (FKDGameplayEffectContext* KDEffectContext = static_cast<FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		KDEffectContext->SetDebuffFrequency(bInFrequency);
	}
}

void UKDAbilitySystemLibrary::SetDamageType(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, const FGameplayTag& InDamageType)
{
	if (FKDGameplayEffectContext* KDEffectContext = static_cast<FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		const TSharedPtr<FGameplayTag> DamageType = MakeShared<FGameplayTag>(InDamageType);
		KDEffectContext->SetDamageType(DamageType);
	}
}

void UKDAbilitySystemLibrary::SetDeathImpulse(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, const FVector& InImpulse)
{
	if (FKDGameplayEffectContext* KDEffectContext = static_cast<FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		KDEffectContext->SetDeathImpulse(InImpulse);
	}
}

void UKDAbilitySystemLibrary::SetKnockbackForce(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, const FVector& InForce)
{
	if (FKDGameplayEffectContext* KDEffectContext = static_cast<FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		KDEffectContext->SetKnockbackForce(InForce);
	}
}

void UKDAbilitySystemLibrary::SetIsRadialDamage(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, const bool bInIsRadialDamage)
{
	if (FKDGameplayEffectContext* KDEffectContext = static_cast<FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		KDEffectContext->SetIsRadialDamage(bInIsRadialDamage);
	}
}

void UKDAbilitySystemLibrary::SetRadialDamageInnerRadius(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, float InInnerRadius)
{
	if (FKDGameplayEffectContext* KDEffectContext = static_cast<FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		KDEffectContext->SetRadialDamageInnerRadius(InInnerRadius);
	}
}

void UKDAbilitySystemLibrary::SetRadialDamageOuterRadius(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, float InOuterRadius)
{
	if (FKDGameplayEffectContext* KDEffectContext = static_cast<FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		KDEffectContext->SetRadialDamageOuterRadius(InOuterRadius);
	}
}

void UKDAbilitySystemLibrary::SetRadialDamageOrigin(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, const FVector& InOrigin)
{
	if (FKDGameplayEffectContext* KDEffectContext = static_cast<FKDGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		KDEffectContext->SetRadialDamageOrigin(InOrigin);
	}
}

void UKDAbilitySystemLibrary::GetLivePlayersWithinRadius(const UObject* WorldContextObject, 
	TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, 
	float Radius, const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		TArray<FOverlapResult> Overlaps;
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);
		for (FOverlapResult& Overlap : Overlaps)
		{
			if (Overlap.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(Overlap.GetActor()))
			{
				OutOverlappingActors.AddUnique(ICombatInterface::Execute_GetAvatar(Overlap.GetActor()));
			}
		}
	}
}

void UKDAbilitySystemLibrary::GetClosestTargets(int32 MaxTargets, const TArray<AActor*>& Actors, TArray<AActor*>& OutClosestTargets, const FVector& Origin)
{
	if (Actors.Num() <= MaxTargets)
	{
		OutClosestTargets = Actors;
		return;
	}

	TArray<AActor*> ActorsToCheck = Actors;
	int32 NumTargetsFound = 0;

	while (NumTargetsFound < MaxTargets)
	{
		if (ActorsToCheck.Num() == 0) break;

		double ClosestDistance = TNumericLimits<double>::Max();
		AActor* ClosestActor;

		for (AActor* PotentialTarget : ActorsToCheck)
		{
			const double Distance = (PotentialTarget->GetActorLocation() - Origin).Length();

			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				ClosestActor = PotentialTarget;
			}
		}
		ActorsToCheck.Remove(ClosestActor);
		OutClosestTargets.AddUnique(ClosestActor);
		++NumTargetsFound;
	}

}

bool UKDAbilitySystemLibrary::IsNotFriend(AActor* FirstActor, AActor* SecondActor)
{
	const bool bFirstIsPlayer = FirstActor->ActorHasTag(FName("Player"));
	const bool bSecondIsPlayer = SecondActor->ActorHasTag(FName("Player"));
	const bool bFirstIsEnemy = FirstActor->ActorHasTag(FName("Enemy"));
	const bool bSecondIsEnemy = SecondActor->ActorHasTag(FName("Enemy"));

	const bool bBothArePlayers = bFirstIsPlayer && bSecondIsPlayer;
	const bool bBothAreEnemies = bFirstIsEnemy && bSecondIsEnemy;
	const bool bFriends = bBothArePlayers || bBothAreEnemies;

	return !bFriends;
}

FGameplayEffectContextHandle UKDAbilitySystemLibrary::ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams)
{
	const FKDGameplayTags& GameplayTags = FKDGameplayTags::Get();
	const AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();

	FGameplayEffectContextHandle EffectContextHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(SourceAvatarActor);

	SetDeathImpulse(EffectContextHandle, DamageEffectParams.DeathImpulse);
	SetKnockbackForce(EffectContextHandle, DamageEffectParams.KnockbackForce);

	SetIsRadialDamage(EffectContextHandle, DamageEffectParams.bIsRadialDamage);
	SetRadialDamageInnerRadius(EffectContextHandle, DamageEffectParams.RadialDamageInnerRadius);
	SetRadialDamageOuterRadius(EffectContextHandle, DamageEffectParams.RadialDamageOuterRadius);
	SetRadialDamageOrigin(EffectContextHandle, DamageEffectParams.RadialDamageOrigin);

	const FGameplayEffectSpecHandle SpecHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeOutgoingSpec(DamageEffectParams.DamageGameplayEffectClass, DamageEffectParams.AbilityLevel, EffectContextHandle);

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageEffectParams.DamageType, DamageEffectParams.BaseDamage);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Chance, DamageEffectParams.DebuffChance);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Damage, DamageEffectParams.DebuffDamage);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Duration, DamageEffectParams.DebuffDuration);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Frequency, DamageEffectParams.DebuffFrequency);

	DamageEffectParams.TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);

	return EffectContextHandle;
}

TArray<FRotator> UKDAbilitySystemLibrary::EvenlySpacedRotators(const FVector& Forward, const FVector& Axis, float Spread, int32 NumRotators)
{
	TArray<FRotator> Rotators;

	const FVector LeftOfSpread = Forward.RotateAngleAxis(-Spread / 2.0f, Axis);
	if (NumRotators > 1)
	{
		const float DeltaSpread = Spread / (NumRotators - 1);
		for (int32 i = 0; i < NumRotators; i++)
		{
			const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
			Rotators.Add(Direction.Rotation());
		}
	}
	else
	{
		Rotators.Add(Forward.Rotation());
	}

	return Rotators;
}

TArray<FVector> UKDAbilitySystemLibrary::EvenlyRotatedVectors(const FVector& Forward, const FVector& Axis, float Spread, int32 NumVectors)
{
	TArray<FVector> Vectors;

	const FVector LeftOfSpread = Forward.RotateAngleAxis(-Spread / 2.0f, Axis);
	if (NumVectors > 1)
	{
		const float DeltaSpread = Spread / (NumVectors - 1);
		for (int32 i = 0; i < NumVectors; i++)
		{
			const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
			Vectors.Add(Direction);
		}
	}
	else
	{
		Vectors.Add(Forward);
	}

	return Vectors;
}
