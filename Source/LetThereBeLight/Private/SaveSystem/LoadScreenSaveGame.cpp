// Copyright ASKD Games


#include "SaveSystem/LoadScreenSaveGame.h"
#include "Abilities/GameplayAbility.h"

FSavedMap ULoadScreenSaveGame::GetSavedMapWithMapName(const FString& InMapName)
{
    for (const FSavedMap Map : SavedMaps)
    {
        if (Map.MapAssetName == InMapName)
        {
            return Map;
        }
    }

    return FSavedMap();
}

bool ULoadScreenSaveGame::HasMap(const FString& InMapName)
{
    for (const FSavedMap Map : SavedMaps)
    {
        if (Map.MapAssetName == InMapName)
        {
            return true;
        }
    }

    return false;
}
