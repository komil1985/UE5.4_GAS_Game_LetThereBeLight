// Copyright ASKD Games


#include "Input/KDInputConfig.h"
#include "EnhancedInput/Public/InputAction.h"

const UInputAction* UKDInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FKDInputAction& Action : AbilityInputAction)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s] "), *InputTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
