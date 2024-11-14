// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "KDAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API UKDAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UKDAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
	
};
