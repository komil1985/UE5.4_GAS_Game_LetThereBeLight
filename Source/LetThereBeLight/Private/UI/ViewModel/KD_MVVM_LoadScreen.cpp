// Copyright ASKD Games


#include "UI/ViewModel/KD_MVVM_LoadScreen.h"
#include "UI/ViewModel/MVVM_LoadSlot.h"
#include "GameMode/MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/KDGameInstance.h"

void UKD_MVVM_LoadScreen::InitializeLoadSlots()
{
	LoadSlot_0 = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
	LoadSlot_0->SetLoadSlotName(FString("LoadSlot_0"));
	LoadSlot_0->SlotIndex = 0;
	LoadSlots.Add(0, LoadSlot_0);
	
	LoadSlot_1 = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
	LoadSlot_1->SetLoadSlotName(FString("LoadSlot_1"));
	LoadSlot_1->SlotIndex = 1;
	LoadSlots.Add(1, LoadSlot_1);

	LoadSlot_2 = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
	LoadSlot_2->SetLoadSlotName(FString("LoadSlot_2"));
	LoadSlot_2->SlotIndex = 2;
	LoadSlots.Add(2, LoadSlot_2);

	SetNumLoadSlots(LoadSlots.Num());
}

UMVVM_LoadSlot* UKD_MVVM_LoadScreen::GetLoadSlotViewModelByIndex(int32 Index) const
{
	return LoadSlots.FindChecked(Index);
}

void UKD_MVVM_LoadScreen::NewSlotButtonPressed(int32 Slot, const FString& EnteredName)
{
	AMyGameModeBase* KDGameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));

	LoadSlots[Slot]->SetMapName(KDGameMode->DefaultMapName);
	LoadSlots[Slot]->SetPlayerName(EnteredName);
	LoadSlots[Slot]->SlotStatus = Taken;
	LoadSlots[Slot]->PlayerStartTag = KDGameMode->DefaultPlayerStartTag;
	
	KDGameMode->SaveSlotData(LoadSlots[Slot], Slot);
	LoadSlots[Slot]->InitializeSlot();

	UKDGameInstance* KDGameInstance = Cast<UKDGameInstance>(KDGameMode->GetGameInstance());
	KDGameInstance->LoadSlotName = LoadSlots[Slot]->GetLoadSlotName();
	KDGameInstance->LoadSlotIndex = LoadSlots[Slot]->SlotIndex;
	KDGameInstance->PlayerStartTag = KDGameMode->DefaultPlayerStartTag;

}

void UKD_MVVM_LoadScreen::NewGameButtonPressed(int32 Slot)
{
	LoadSlots[Slot]->SetWidgetSwitcherIndex.Broadcast(1);
}

void UKD_MVVM_LoadScreen::SelectSlotButtonPressed(int32 Slot)
{
	SlotSelected.Broadcast();
	for (const TTuple<int32, UMVVM_LoadSlot*> LoadSlot : LoadSlots)
	{
		if (LoadSlot.Key == Slot)
		{
			LoadSlot.Value->EnableSelectSlotButton.Broadcast(false);
		}
		else
		{
			LoadSlot.Value->EnableSelectSlotButton.Broadcast(true);
		}
	}
	SelectedSlot = LoadSlots[Slot];
}

void UKD_MVVM_LoadScreen::YesButtonPressed()
{
	if (IsValid(SelectedSlot))
	{
		AMyGameModeBase::DeleteSlot(SelectedSlot->GetLoadSlotName(), SelectedSlot->SlotIndex);
		SelectedSlot->SlotStatus = Vacant;
		SelectedSlot->InitializeSlot();
		SelectedSlot->EnableSelectSlotButton.Broadcast(true);
	}
}

void UKD_MVVM_LoadScreen::PlayButtonPressed()
{
	AMyGameModeBase* KDGameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));
	UKDGameInstance* KDGameInstance = Cast<UKDGameInstance>(KDGameMode->GetGameInstance());
	KDGameInstance->PlayerStartTag = SelectedSlot->PlayerStartTag;
	KDGameInstance->LoadSlotName = SelectedSlot->GetLoadSlotName();
	KDGameInstance->LoadSlotIndex = SelectedSlot->SlotIndex;

	if (IsValid(SelectedSlot))
	{
		KDGameMode->TravelToMap(SelectedSlot);
	}
	
}

void UKD_MVVM_LoadScreen::LoadData()
{
	AMyGameModeBase* KDGameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));

	for (const TTuple<int32, UMVVM_LoadSlot*> LoadSlot : LoadSlots)
	{
		ULoadScreenSaveGame* SaveGameObject = KDGameMode->GetSaveSlotData(LoadSlot.Value->GetLoadSlotName(), LoadSlot.Key);
		const FString PlayerName = SaveGameObject->PlayerName;
		TEnumAsByte<ESaveSlotStatus> SaveSlotStatus = SaveGameObject->SaveSlotStatus;

		LoadSlot.Value->SlotStatus = SaveSlotStatus;
		LoadSlot.Value->SetPlayerName(PlayerName);
		LoadSlot.Value->InitializeSlot();
		LoadSlot.Value->SetMapName(SaveGameObject->MapName);
		LoadSlot.Value->PlayerStartTag = SaveGameObject->PlayerStartTag;
	}
}

void UKD_MVVM_LoadScreen::SetNumLoadSlots(int32 InNumLoadSlots)
{
	UE_MVVM_SET_PROPERTY_VALUE(NumLoadSlots, InNumLoadSlots);
}
