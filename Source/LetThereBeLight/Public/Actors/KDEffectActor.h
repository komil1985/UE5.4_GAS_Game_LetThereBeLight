// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KDEffectActor.generated.h"


class UGameplayEffect;

UCLASS()
class LETTHEREBELIGHT_API AKDEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AKDEffectActor();


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Effects Applied")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);
};
