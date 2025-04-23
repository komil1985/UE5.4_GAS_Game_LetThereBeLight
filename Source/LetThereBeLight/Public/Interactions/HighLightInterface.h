// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HighLightInterface.generated.h"

UINTERFACE(MinimalAPI)
class UHighLightInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LETTHEREBELIGHT_API IHighLightInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void HighlightActor();

	UFUNCTION(BlueprintNativeEvent)
	void UnHighlightActor();

};
