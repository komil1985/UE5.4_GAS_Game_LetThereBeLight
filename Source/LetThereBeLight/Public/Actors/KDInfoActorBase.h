// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactions/KDInteractable.h"
#include "KDInfoActorBase.generated.h"

class UStaticMeshComponent;
class UWidgetComponent;
class USphereComponent;
UCLASS()
class LETTHEREBELIGHT_API AKDInfoActorBase : public AActor, public IKDInteractable
{
	GENERATED_BODY()
	
public:	
	AKDInfoActorBase();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr <UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr <UWidgetComponent> Widget;

	UFUNCTION(BlueprintCallable, Category = "Interact")
	virtual void Interact_Implementation() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

private:
	bool bIsBig;
};
