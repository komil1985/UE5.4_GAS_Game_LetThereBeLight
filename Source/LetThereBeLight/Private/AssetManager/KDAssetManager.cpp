// Copyright ASKD Games


#include "AssetManager/KDAssetManager.h"
#include "Misc/KDGameplayTags.h"
#include <AbilitySystemGlobals.h>

UKDAssetManager& UKDAssetManager::Get()
{
	// TODO: insert return statement here
	check(GEngine);

	UKDAssetManager* AssetManager = Cast<UKDAssetManager>(GEngine->AssetManager);
	return *AssetManager;
}

void UKDAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FKDGameplayTags::InitializeNativeGameplayTags();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
