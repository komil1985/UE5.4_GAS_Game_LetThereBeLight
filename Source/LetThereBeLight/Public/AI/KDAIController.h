// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "KDAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API AKDAIController : public AAIController
{
	GENERATED_BODY()

public:
	AKDAIController();
	
protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
