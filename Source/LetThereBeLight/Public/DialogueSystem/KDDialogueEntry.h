// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "KDDialogueEntry.generated.h"


USTRUCT(BlueprintType)
struct FDialogueEntry : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Speaker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NextID = -1;
};
/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API UKDDialogueEntry : public UDataTable
{
	GENERATED_BODY()
	
};
