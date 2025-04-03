// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Actors/KDProjectile.h"
#include "KDProjectileFireBall.generated.h"

/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API AKDProjectileFireBall : public AKDProjectile
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
};
