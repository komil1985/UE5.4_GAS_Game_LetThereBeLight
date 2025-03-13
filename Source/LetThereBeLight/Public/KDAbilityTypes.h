// Copyright ASKD Games

#pragma once

#include "GameplayEffectTypes.h"
#include "KDAbilityTypes.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FDamageEffectParams
{
	GENERATED_BODY();

	FDamageEffectParams() {}

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UObject> WorldContextObject = nullptr;

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> DamageGameplayEffectClass = nullptr;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> SourceAbilitySystemComponent;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> TargetAbilitySystemComponent;

	UPROPERTY(BlueprintReadWrite)
	float BaseDamage = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	float AbilityLevel = 1.0f;

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag DamageType = FGameplayTag();

	UPROPERTY(BlueprintReadWrite)
	float DebuffChance = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	float DebuffDamage = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	float DebuffDuration = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	float DebuffFrequency = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	float DeathImpulseMagnitude = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	FVector DeathImpulse = FVector::ZeroVector;
};


USTRUCT(BlueprintType)
struct FKDGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	// Getters
	bool IsBlockedHit() const { return bIsBlockedHit; }
	bool IsCriticalHit() const { return bIsCriticalHit; }
	bool IsSuccessfulDebuff() const { return bIsSuccessfulDebuff; }
	float GetDebuffDamage() const { return DebuffDamage; }
	float GetDebuffDuration() const{ return DebuffDuration; }
	float GetDebuffFrequency() const { return DebuffFrequency; }
	TSharedPtr<FGameplayTag> GetDamageType() const { return DamageType; }
	FVector GetDeathImpulse() const { return DeathImpulse; }

	// Setters
	void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }
	void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	void SetIsSuccessfulDebuff(bool bInIsDebuff) { bIsSuccessfulDebuff = bInIsDebuff; }
	void SetDebuffDamage(float InDamage) { DebuffDamage = InDamage; }
	void SetDebuffDuration(float InDuration) { DebuffDuration = InDuration; }
	void SetDebuffFrequency(float InFrequency) { DebuffFrequency = InFrequency; }
	void SetDamageType(TSharedPtr<FGameplayTag>InDamageType) { DamageType = InDamageType; }
	void SetDeathImpulse(const FVector& InImpulse) { DeathImpulse = InImpulse; }

	// Returns the actual struct used for serialization, subclasses must override this
	virtual UScriptStruct* GetScriptStruct() const { return FGameplayEffectContext::StaticStruct(); }

	// Creates a copy of this context, used to duplicate for later modifications
	virtual FGameplayEffectContext* Duplicate() const
	{
		FGameplayEffectContext* NewContext = new FGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of HitResult
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	// Custom serialization, subclasses must override this
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

protected:
	UPROPERTY()
	bool bIsBlockedHit = false;

	UPROPERTY()
	bool bIsCriticalHit = false;

	UPROPERTY()
	bool bIsSuccessfulDebuff = false;

	UPROPERTY()
	float DebuffDamage = 0.0f;

	UPROPERTY()
	float DebuffDuration = 0.0f;

	UPROPERTY()
	float DebuffFrequency = 0.0f;

	TSharedPtr<FGameplayTag> DamageType;

	UPROPERTY()
	FVector DeathImpulse = FVector::ZeroVector;

};


template<>
struct TStructOpsTypeTraits<FKDGameplayEffectContext> : public TStructOpsTypeTraitsBase2 <FKDGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};
