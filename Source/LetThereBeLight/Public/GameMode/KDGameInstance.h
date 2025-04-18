// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "KDGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API UKDGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FName PlayerStartTag = FName();

	UPROPERTY()
	FString LoadSlotName = FString();

	UPROPERTY()
	int32 LoadSlotIndex = 0;
	
};
