// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactions/KDInteractable.h"
#include "KDInfoActorBase.generated.h"

UENUM(BlueprintType)
enum class ESelectedInteractType : uint8
{
	Information,
	Dialogue
};

class UStaticMeshComponent;
class UWidgetComponent;
class USphereComponent;
class USceneComponent;

UCLASS()
class LETTHEREBELIGHT_API AKDInfoActorBase : public AActor, public IKDInteractable
{
	GENERATED_BODY()
	
public:	
	AKDInfoActorBase();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	ESelectedInteractType SelectedInteractionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	TArray<FText>TextSequence;

	virtual void CanInteract_Implementation() override;
	virtual void StartInteract_Implementation() override;
	virtual void StopInteract_Implementation() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr <UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr <UWidgetComponent> Widget;

	UFUNCTION()
	virtual void Interact_Implementation() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	TMap<ESelectedInteractType, TSubclassOf<UUserWidget>> InteractionTypeMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	TSubclassOf<UUserWidget> WidgetToDisplay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	TObjectPtr<UUserWidget> DisplayedWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	int32 TextToDisplay = 0;

private:
	bool bIsBig;
};
