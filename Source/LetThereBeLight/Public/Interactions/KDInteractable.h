// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KDInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UKDInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LETTHEREBELIGHT_API IKDInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void CanInteract();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void StoptInteract();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void Interact();
};
