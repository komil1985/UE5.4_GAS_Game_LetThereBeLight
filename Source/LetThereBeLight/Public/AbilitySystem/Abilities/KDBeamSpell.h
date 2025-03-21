// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/KDDamageGameplayAbility.h"
#include "KDBeamSpell.generated.h"

class ACharacter;
/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API UKDBeamSpell : public UKDDamageGameplayAbility
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void StoreMouseDataInfo(const FHitResult& HitResult);

	UFUNCTION(BlueprintCallable)
	void StoreOwnerVariables();

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Beam")
	FVector MouseHitLocation;

	UPROPERTY(BlueprintReadWrite, Category = "Beam")
	TObjectPtr<AActor> MouseHitActor;

	UPROPERTY(BlueprintReadWrite, Category = "Beam")
	TObjectPtr<APlayerController> OwnerPlayerController;

	UPROPERTY(BlueprintReadWrite, Category = "Beam")
	TObjectPtr<ACharacter> OwnerCharacter;
};
