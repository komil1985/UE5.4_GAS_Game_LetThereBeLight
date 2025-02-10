// Copyright ASKD Games


#include "AbilitySystem/Data/AttributeInfo.h"
#include "LetThereBeLight/KDLogChannles.h"

FKDAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FKDAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogKD, Error, TEXT("Can't find into for AttributeTag [%s] on AttributeInfo [%s]."),
			*AttributeTag.ToString(), *GetNameSafe(this));
	}

	return FKDAttributeInfo();
}
