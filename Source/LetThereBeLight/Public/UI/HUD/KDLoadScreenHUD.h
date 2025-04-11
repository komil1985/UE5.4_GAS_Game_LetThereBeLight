// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KDLoadScreenHUD.generated.h"

class UKDLoadScreenWidget;
class UKD_MVVM_LoadScreen;

/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API AKDLoadScreenHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LoadScreenWidgetClass;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UKDLoadScreenWidget>LoadScreenWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UKD_MVVM_LoadScreen> LoadScreenViewModelClass;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UKD_MVVM_LoadScreen> LoadScreenViewModel;


protected:
	virtual void BeginPlay() override;
	
};
