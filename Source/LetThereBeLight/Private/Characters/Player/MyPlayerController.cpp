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
#include <NiagaraFunctionLibrary.h>
#include "Actors/MagicCircle.h"
#include "Components/DecalComponent.h"
#include "LetThereBeLight/LetThereBeLight.h"
#include "Interactions/HighLightInterface.h"



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
	UpdateMagicCircleLocation();
}

void AMyPlayerController::ShowMagicCircle(UMaterialInterface* DecalMaterial)
{
	if (!IsValid(MagicCircle))
	{
		MagicCircle = GetWorld()->SpawnActor<AMagicCircle>(MagicCircleClass);

		if (DecalMaterial)
		{
			MagicCircle->MagicCircleDecal->SetMaterial(0, DecalMaterial);
		}
	}
}

void AMyPlayerController::HideMagicCircle()
{
	if (IsValid(MagicCircle))
	{
		MagicCircle->Destroy();
	}
}

void AMyPlayerController::UpdateMagicCircleLocation()
{
	if (IsValid(MagicCircle))
	{
		MagicCircle->SetActorLocation(CursorHit.ImpactPoint);
	}
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
	if (GetKDASC() && GetKDASC()->HasMatchingGameplayTag(FKDGameplayTags::Get().Player_Block_CursorTrace))
	{
		UnHighlightActor(LastActor);
		UnHighlightActor(ThisActor);
		LastActor = nullptr;
		ThisActor = nullptr;
		return;
	}

	const ECollisionChannel TraceChannel = IsValid(MagicCircle) ? ECC_ExcludeCharacters : ECC_Visibility;
	GetHitResultUnderCursor(TraceChannel, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	if (IsValid(CursorHit.GetActor()) && CursorHit.GetActor()->Implements<UHighLightInterface>())
	{
		ThisActor = CursorHit.GetActor();
	}
	else
	{
		ThisActor = nullptr;
	}
	
	if (LastActor != ThisActor)
	{
		UnHighlightActor(LastActor);
		HighlightActor(ThisActor);
	}
}


void AMyPlayerController::HighlightActor(AActor* InActor)
{
	if (IsValid(InActor) && InActor->Implements<UHighLightInterface>())
	{
		IHighLightInterface::Execute_HighlightActor(InActor);
	}
}

void AMyPlayerController::UnHighlightActor(AActor* InActor)
{
	if (IsValid(InActor) && InActor->Implements<UHighLightInterface>())
	{
		IHighLightInterface::Execute_UnHighlightActor(InActor);
	}
}

void AMyPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (GetKDASC() && GetKDASC()->HasMatchingGameplayTag(FKDGameplayTags::Get().Player_Block_InputPressed))
	{
		return;
	}

	if(InputTag.MatchesTagExact(FKDGameplayTags::Get().InputTag_LMB))
	{
		if (IsValid(ThisActor))
		{
			TargetingStatus = ThisActor->Implements<UEnemyInterface>() ? ETargetingStatus::TargetingEnemy : ETargetingStatus::TargetingNonEnemy;
			bAutoRunning = false;
		}
		else
		{
			TargetingStatus = ETargetingStatus::NotTargeting;
		}
	}
	if (GetKDASC()) GetKDASC()->AbilityInputTagPressed(InputTag);
}

void AMyPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetKDASC() && GetKDASC()->HasMatchingGameplayTag(FKDGameplayTags::Get().Player_Block_InputReleased))
	{
		return;
	}
	if (!InputTag.MatchesTagExact(FKDGameplayTags::Get().InputTag_LMB))
	{
		if (GetKDASC())
		{
			GetKDASC()->AbilityInputTagReleased(InputTag);
		}
		return;
	}

	if (GetKDASC()) GetKDASC()->AbilityInputTagReleased(InputTag);

	if (TargetingStatus != ETargetingStatus::TargetingEnemy && !bIsShiftKeyDown)
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
			if (GetKDASC() && !GetKDASC()->HasMatchingGameplayTag(FKDGameplayTags::Get().Player_Block_InputPressed))
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ClickNiagaraSystem, CachedDestination);
			}
		}
		FollowTime = 0.0f;
		TargetingStatus = ETargetingStatus::NotTargeting;
	}
}

void AMyPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetKDASC() && GetKDASC()->HasMatchingGameplayTag(FKDGameplayTags::Get().Player_Block_InputHeld))
	{
		return;
	}
	if (!InputTag.MatchesTagExact(FKDGameplayTags::Get().InputTag_LMB))
	{
		if (GetKDASC())
		{
			GetKDASC()->AbilityInputTagHeld(InputTag);
		}
		return;
	}

	if (TargetingStatus == ETargetingStatus::TargetingEnemy || bIsShiftKeyDown)
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
	if (GetKDASC() && GetKDASC()->HasMatchingGameplayTag(FKDGameplayTags::Get().Player_Block_InputPressed))
	{
		return;
	}
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
