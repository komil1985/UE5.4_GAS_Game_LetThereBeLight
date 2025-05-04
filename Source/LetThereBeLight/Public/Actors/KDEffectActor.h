// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "KDEffectActor.generated.h"

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovePolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

class UGameplayEffect;
class UAbilitySystemComponent;
UCLASS()
class LETTHEREBELIGHT_API AKDEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AKDEffectActor();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	FVector CalculatedLocation;

	UPROPERTY(BlueprintReadWrite)
	FRotator CalculatedRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	bool bRotates = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	float RotationRate = 45.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	bool bSinusoidalMovement = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	float SineAmplitude = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	float SinePeriodConstant = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	FVector InitialLocation;

	UFUNCTION(BlueprintCallable)
	void StartSinusoidalMovement();

	UFUNCTION(BlueprintCallable)
	void StartRotation();

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	/////////////////////////////////////////////////////////////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects Applied")
	bool bDestroyOnEffectRemoval = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects Applied")
	bool bApplyEffectsToEnemies = false;

	//////////////////////// Instant Effect /////////////////////////////////////////////////////////
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects Applied")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects Applied")
	EEffectApplicationPolicy  InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	///////////////////////// Duration Effect ///////////////////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = "Effects Applied")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects Applied")
	EEffectApplicationPolicy  DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	////////////////////////// Infinite Effect //////////////////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects Applied")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects Applied")
	EEffectApplicationPolicy  InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects Applied")
	EEffectRemovePolicy InfiniteEffectRemovalPolicy = EEffectRemovePolicy::RemoveOnEndOverlap;

	/////////////////////////////////////////////////////////////////////////////////////////////////

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*>  ActiveGameplayEffectHandles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects Applied")
	float ActorLevel = 1.0f;

private:
	float RunningTime = 0.0f;
	void ItemMovement(float DeltaTime);
};
