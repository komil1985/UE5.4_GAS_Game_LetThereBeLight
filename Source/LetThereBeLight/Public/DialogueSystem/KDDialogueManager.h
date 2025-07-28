// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "DialogueSystem/KDDialogueEntry.h"
#include "KDDialogueManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDialogueUpdated, const FString&, Speaker, const FText&, Text);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueEnded);

UCLASS()
class LETTHEREBELIGHT_API AKDDialogueManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AKDDialogueManager();

	static AKDDialogueManager* GetDialogueManager(UWorld* World);

	UPROPERTY(EditAnywhere, Category = "Dialogue")
	UDataTable* DialogueDataTable;

	UFUNCTION(BlueprintCallable)
	void StartDialogue(AActor* NPC);

	UFUNCTION(BlueprintCallable)
	void NextDialogue();

	UPROPERTY(BlueprintAssignable)
	FOnDialogueUpdated OnDialogueUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnDialogueEnded OnDialogueEnded;

protected:
	int32 CurrentDialogueID;
	AActor* CurrentNPC;

	const FDialogueEntry* GetDialogueEntry(int32 EntryID) const;

};
