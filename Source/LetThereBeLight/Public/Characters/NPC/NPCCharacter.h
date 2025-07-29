// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interactions/NPCInterface.h"
#include "NPCCharacter.generated.h"


class USphereComponent;
UCLASS()
class LETTHEREBELIGHT_API ANPCCharacter : public ACharacter, public INPCInterface
{
	GENERATED_BODY()

public:
	ANPCCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* InteractionSphere;

	virtual void Interact_Implementation(AActor* Caller) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Dialogue")
	int32 StartingDialogueID = 0;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
