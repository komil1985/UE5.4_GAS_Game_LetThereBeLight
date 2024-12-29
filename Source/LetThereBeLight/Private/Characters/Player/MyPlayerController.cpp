// Copyright ASKD Games


#include "Characters/Player/MyPlayerController.h"
#include "Interactions/EnemyInterface.h"
#include "EnhancedInputSubsystems.h"
#include <Input/KDInputComponent.h>
#include <AbilitySystemBlueprintLibrary.h>
#include "AbilitySystem/KDAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Misc/KDGameplayTags.h"
#include <NavigationSystem.h>
#include "NavigationPath.h"
#include "GameFramework/Character.h"
#include "UI/Widget/FloatingText/DamageTextComponent.h"


AMyPlayerController::AMyPlayerController()
{
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(PlayerContext);
	subsystem();
	MouseCursorMode();

}

void AMyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	AutoRunning();

}

void AMyPlayerController::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharacter, bool bBlockedHit, bool bCriticalHit)
{
	if (IsValid(TargetCharacter) && DamageTextComponentClass && IsLocalController())
	{
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount, bBlockedHit, bCriticalHit);
	}
}

void AMyPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();
	
	if (LastActor != ThisActor)
	{
		if (LastActor)
		{
			LastActor->UnHighlightActor();
		}
		if (ThisActor)
		{
			ThisActor->HighlightActor();
		}
	}

}

///////////////////////////////////////////////////////////////////////////////////

void AMyPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if(InputTag.MatchesTagExact(FKDGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}

}

void AMyPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FKDGameplayTags::Get().InputTag_LMB))
	{
		if (GetKDASC())
		{
			GetKDASC()->AbilityInputTagReleased(InputTag);
		}
		return;
	}

	if (GetKDASC()) GetKDASC()->AbilityInputTagReleased(InputTag);

	if (!bTargeting && !bIsShiftKeyDown)
	{		
		// Check for short press
		const APawn* ControlledPawn = GetPawn();
		if (FollowTime <= ShortPressedThreshold && ControlledPawn)
		{
			UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination);
			if (NavPath)
			{
				Spline->ClearSplinePoints();
				for (const FVector& PointLocation : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLocation, ESplineCoordinateSpace::World);
				}
				if (NavPath->PathPoints.Num() > 0)
				{
					CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
					bAutoRunning = true;
				}
			}
		}
		FollowTime = 0.0f;
		bTargeting = false;
	}
}

void AMyPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FKDGameplayTags::Get().InputTag_LMB))
	{
		if (GetKDASC())
		{
			GetKDASC()->AbilityInputTagHeld(InputTag);
		}
		return;
	}

	if (bTargeting || bIsShiftKeyDown)
	{
		if (GetKDASC())
		{
			GetKDASC()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();

		if (CursorHit.bBlockingHit)
		{
			CachedDestination = CursorHit.ImpactPoint;
		}

		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}

}

///////////////////////////////////////////////////////////////////////////////////

UKDAbilitySystemComponent* AMyPlayerController::GetKDASC()
{
	if (KDAbilitySystemComponent == nullptr)
	{
		KDAbilitySystemComponent = Cast<UKDAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return KDAbilitySystemComponent;
}

void AMyPlayerController::AutoRunning()
{
	if (!bAutoRunning) return;
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);

		ControlledPawn->AddMovementInput(Direction);
		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}

void AMyPlayerController::MouseCursorMode()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AMyPlayerController::subsystem()
{
	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (SubSystem) 
	{
		SubSystem->AddMappingContext(PlayerContext, 0);
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UKDInputComponent* KDInputComponent = CastChecked<UKDInputComponent>(InputComponent);
	KDInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);
	KDInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &AMyPlayerController::ShiftPressed);
	KDInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &AMyPlayerController::ShiftReleased);
	KDInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AMyPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
