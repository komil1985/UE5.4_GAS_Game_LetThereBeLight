// Copyright ASKD Games


#include "UI/ViewModel/KD_MVVM_LoadScreen.h"
#include "UI/ViewModel/MVVM_LoadSlot.h"
#include "GameMode/MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UKD_MVVM_LoadScreen::InitializeLoadSlots()
{
	LoadSlot_0 = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
	LoadSlot_0->LoadSlotName = FString("LoadSlot_0");
	LoadSlots.Add(0, LoadSlot_0);

	LoadSlot_1 = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
	LoadSlots.Add(1, LoadSlot_1);
	LoadSlot_1->LoadSlotName = FString("LoadSlot_1");

	LoadSlot_2 = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
	LoadSlots.Add(2, LoadSlot_2);
	LoadSlot_2->LoadSlotName = FString("LoadSlot_2");
}

UMVVM_LoadSlot* UKD_MVVM_LoadScreen::GetLoadSlotViewModelByIndex(int32 Index) const
{
	return LoadSlots.FindChecked(Index);
}

void UKD_MVVM_LoadScreen::NewSlotButtonPressed(int32 Slot, const FString& EnteredName)
{
	AMyGameModeBase* KDGameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));

	LoadSlots[Slot]->SetPlayerName(EnteredName);
	
	KDGameMode->SaveSlotData(LoadSlots[Slot], Slot);

	LoadSlots[Slot]->InitializeSlot();
}

void UKD_MVVM_LoadScreen::NewGameButtonPressed(int32 Slot)
{
	LoadSlots[Slot]->SetWidgetSwitcherIndex.Broadcast(1);
}

void UKD_MVVM_LoadScreen::SelectSlotButtonPressed(int32 Slot)
{

}
