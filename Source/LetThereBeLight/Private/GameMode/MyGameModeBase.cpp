// Copyright ASKD Games


#include "GameMode/MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/ViewModel/MVVM_LoadSlot.h"
#include "GameFramework/SaveGame.h"
#include "SaveSystem/LoadScreenSaveGame.h"

void AMyGameModeBase::SaveSlotData(UMVVM_LoadSlot* LoadSlot, int32 SlotIndex)
{
	if (UGameplayStatics::DoesSaveGameExist(LoadSlot->LoadSlotName, SlotIndex))
	{
		UGameplayStatics::DeleteGameInSlot(LoadSlot->LoadSlotName, SlotIndex);
	}

	USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(LoadScreenSaveGameClass);
	
	ULoadScreenSaveGame* LoadScreenSaveGame = Cast<ULoadScreenSaveGame>(SaveGameObject);
	LoadScreenSaveGame->PlayerName = LoadSlot->PlayerName;

	UGameplayStatics::SaveGameToSlot(LoadScreenSaveGame, LoadSlot->LoadSlotName, SlotIndex);
}
