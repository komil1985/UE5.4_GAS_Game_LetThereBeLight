// Copyright ASKD Games


#include "DialogueSystem/KDDialogueManager.h"
#include "EngineUtils.h"

AKDDialogueManager::AKDDialogueManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

AKDDialogueManager* AKDDialogueManager::GetDialogueManager(UWorld* World)
{
	for (TActorIterator<AKDDialogueManager> It(World); It; ++It)
	{
		return *It;
	}
	return nullptr;
}

void AKDDialogueManager::StartDialogue(AActor* NPC)
{
	CurrentNPC = NPC;
	CurrentDialogueID = 0;

	if (const FDialogueEntry* Entry = GetDialogueEntry(CurrentDialogueID))
	{
		OnDialogueUpdated.Broadcast(Entry->Speaker, Entry->Text);
	}
}

void AKDDialogueManager::NextDialogue()
{
	if (const FDialogueEntry* CurrentEntry = GetDialogueEntry(CurrentDialogueID))
	{
		int32 NextID = CurrentEntry->NextID;

		if (NextID == -1)
		{
			OnDialogueEnded.Broadcast();
			CurrentNPC = nullptr;
		}
		else
		{
			CurrentDialogueID = NextID;
			if (const FDialogueEntry* NextEntry = GetDialogueEntry(CurrentDialogueID))
			{
				OnDialogueUpdated.Broadcast(NextEntry->Speaker, NextEntry->Text);
			}
		}
	}
}

const FDialogueEntry* AKDDialogueManager::GetDialogueEntry(int32 EntryID) const
{
	if (!DialogueDataTable) return nullptr;

	static const FString Context = "Dialogue Context";
	return DialogueDataTable->FindRow<FDialogueEntry>(FName(*FString::FromInt(EntryID)), Context);
}