// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/KDGameplayAbility.h"
#include "KDProjectileSpell.generated.h"

class AKDProjectile;
/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API UKDProjectileSpell : public UKDGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AKDProjectile> ProjectileClass;
};
