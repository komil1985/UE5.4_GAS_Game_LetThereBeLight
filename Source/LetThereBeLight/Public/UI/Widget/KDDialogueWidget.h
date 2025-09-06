// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "KDDialogueWidget.generated.h"

/**
 * 
 */
class UTextBlock;
UCLASS()
class LETTHEREBELIGHT_API UKDDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MyTextBlock;

	UFUNCTION(BlueprintCallable, Category = "Dialogue Widget")
	void SetDilogueText(const FText& InText);

};
