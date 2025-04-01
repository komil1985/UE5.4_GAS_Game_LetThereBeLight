// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/KDBeamSpell.h"
#include "LightningBeam.generated.h"

/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API ULightningBeam : public UKDBeamSpell
{
	GENERATED_BODY()
	
public:
	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 Level) override;

};
