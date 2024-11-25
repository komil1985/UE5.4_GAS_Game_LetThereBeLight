// Copyright ASKD Games

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "KDInputConfig.h"
#include "KDInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API UKDInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UKDInputConfig* InputConfig,UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
inline void UKDInputComponent::BindAbilityActions(const UKDInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);

	for (const FKDInputAction& Action : InputConfig->AbilityInputAction)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}

			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}

			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
			}
		}
	}
}
