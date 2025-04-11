// Copyright ASKD Games


#include "UI/HUD/KDLoadScreenHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/KDLoadScreenWidget.h"
#include "UI/ViewModel/KD_MVVM_LoadScreen.h"


void AKDLoadScreenHUD::BeginPlay()
{
	Super::BeginPlay();

	LoadScreenViewModel = NewObject<UKD_MVVM_LoadScreen> (this, LoadScreenViewModelClass);

	LoadScreenWidget = CreateWidget<UKDLoadScreenWidget>(GetWorld(), LoadScreenWidgetClass);
	LoadScreenWidget->AddToViewport();

}
