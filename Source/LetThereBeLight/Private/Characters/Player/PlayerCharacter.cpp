// Copyright ASKD Games


#include "Characters/Player/PlayerCharacter.h"
#include "Characters/Player/MyPlayerState.h"
#include "Characters/Player/MyPlayerController.h"
#include "AbilitySystem/KDAbilitySystemComponent.h"
#include "AbilitySystem/KDAbilitySystemLibrary.h"
#include "AbilitySystem/KDAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/Debuff/DebuffNiagaraComponent.h"
#include "UI/HUD/KDHUD.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "NiagaraComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "Misc/KDGameplayTags.h"
#include "GameMode/MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "SaveSystem/LoadScreenSaveGame.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Interactions/NPCInterface.h"
#include "../KDLogChannles.h"


APlayerCharacter::APlayerCharacter()
{
	PlayerSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("PlayerSpringArm"));
	PlayerSpringArm->SetupAttachment(GetRootComponent());
	PlayerSpringArm->TargetArmLength = 800.0f;
	PlayerSpringArm->bDoCollisionTest = false;
	PlayerSpringArm->bUsePawnControlRotation = true;
	PlayerSpringArm->bInheritPitch = false;
	PlayerSpringArm->bInheritYaw = false;
	PlayerSpringArm->bInheritRoll = false;
	
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(PlayerSpringArm, USpringArmComponent::SocketName);
	PlayerCamera->bUsePawnControlRotation = false;

	CameraBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CameraBoxComponent"));
	CameraBoxComponent->SetupAttachment(PlayerSpringArm, USpringArmComponent::SocketName);
	CameraBoxComponent->SetBoxExtent(FVector(700.0f, 15.0f, 200.0f));

	InteractionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionComponent"));
	InteractionComponent->SetupAttachment(GetRootComponent());
	InteractionComponent->SetBoxExtent(FVector(32.0f, 32.0f, 32.0f));
	InteractionComponent->SetRelativeLocation(FVector(100.0f, 0.0f, 0.0f));
	InteractionComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	InteractionComponent->SetRelativeScale3D(FVector(1.0f, 1.0f, 2.5f));
	InteractionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	InteractionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	InteractionComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);

	LevelUpNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LevelUpNiagaraComponent"));
	LevelUpNiagaraComponent->SetupAttachment(GetRootComponent());
	LevelUpNiagaraComponent->bAutoActivate = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1000.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetMesh()->SetSimulatePhysics(false);

	LineTraceType = ELineTraceType::CAMERA_SINGLE;
	LineTraceDistance = 100.0f;

	CharacterClass = ECharacterClass::Elementalist;
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init Ability actor info for the server
	InitAbilityActorInfo();
	LoadProgress();

	if (AMyGameModeBase* KDGameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		KDGameMode->LoadWorldState(GetWorld());
	}

}

void APlayerCharacter::LoadProgress()
{
	AMyGameModeBase* KDGameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));

	if (KDGameMode)
	{
		ULoadScreenSaveGame* SaveData = KDGameMode->RetrieveInGameSaveData();
		if (SaveData == nullptr) return;

		if (SaveData->bFirstTimeLoadIn)
		{
			InitializeDefaultAttributes();
			AddCharacterAbilities();
		}
		else
		{
			// Load Abilities From Disk
			if (UKDAbilitySystemComponent* KDASC = Cast<UKDAbilitySystemComponent>(AbilitySystemComponent))
			{
				KDASC->AddCharacterAbilitiesFromSaveData(SaveData);
			}

			// Load Player State
			if (AMyPlayerState* KDPlayerState = Cast<AMyPlayerState>(GetPlayerState()))
			{
				KDPlayerState->SetLevel(SaveData->PlayerLevel);
				KDPlayerState->SetXP(SaveData->PlayerXP);
				KDPlayerState->SetAttributePoints(SaveData->AttributePoints);
				KDPlayerState->SetSpellPoints(SaveData->SpellPoints);
			}

			UKDAbilitySystemLibrary::InitilizeDefaultAttributesFromSaveData(this, AbilitySystemComponent, SaveData);
		}
	}
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init Ability actor info for the client
	InitAbilityActorInfo();

}

void APlayerCharacter::Die(const FVector& DeathImpulse)
{
	Super::Die(DeathImpulse);
	//SetLifeSpan(LifeSpan);
	PlayAnimMontage(GetDieMontage(), 1.0f);
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	PlayerController->DisableInput(PlayerController);

	FTimerDelegate DeathTimerDelegate;
	DeathTimerDelegate.BindLambda
	(
		[this]()
		{
			AMyGameModeBase* KDGM = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));
			if (KDGM)
			{
				KDGM->PlayerDied(this);
			}
		}
	);
	GetWorldTimerManager().SetTimer(DeathTimer, DeathTimerDelegate, DeathTime, false);
	PlayerCamera->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

}

int32 APlayerCharacter::GetPlayerLevel_Implementation()
{
	AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	return MyPlayerState->GetPlayerLevel();
}

void APlayerCharacter::AddToXP_Implementation(int32 InXP)
{
	AMyPlayerState* KDPlayerState = GetPlayerState<AMyPlayerState>();
	check(KDPlayerState);
	KDPlayerState->AddToXP(InXP);
}

void APlayerCharacter::LevelUp_Implementation()
{
	MulticastLevelUpParticles();
}

void APlayerCharacter::MulticastLevelUpParticles_Implementation() const
{
	if (IsValid(LevelUpNiagaraComponent))
	{
		const FVector CameraLocation = PlayerCamera->GetComponentLocation();
		const FVector LevelUpNSLocation = LevelUpNiagaraComponent->GetComponentLocation();
		const FRotator ToCameraRotation = (CameraLocation - LevelUpNSLocation).Rotation();
		LevelUpNiagaraComponent->SetWorldRotation(ToCameraRotation);
		LevelUpNiagaraComponent->Activate(true);
	}
}

int32 APlayerCharacter::GetXP_Implementation() const
{
	AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	return MyPlayerState->GetPlayerXP();
}

int32 APlayerCharacter::FindLevelForXP_Implementation(int32 InXP) const
{
	const AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	return MyPlayerState->LevelUpInfo->FindLevelForXP(InXP);
}

int32 APlayerCharacter::GetAttributePointsReward_Implementation(int32 Level) const
{
	const AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	return MyPlayerState->LevelUpInfo->LevelUpInformation[Level].AttributePointAward;
}

int32 APlayerCharacter::GetSpellPointsReward_Implementation(int32 Level) const
{
	const AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	return MyPlayerState->LevelUpInfo->LevelUpInformation[Level].SpellPointAward;
}

void APlayerCharacter::AddToPlayerLevel_Implementation(int32 InPlayerLevel)
{
	AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	MyPlayerState->AddToLevel(InPlayerLevel);

	if (UKDAbilitySystemComponent* KDASC = Cast<UKDAbilitySystemComponent>(GetAbilitySystemComponent()))
	{
		KDASC->UpdateAbilityStatuses(MyPlayerState->GetPlayerLevel());
	}
}

void APlayerCharacter::AddToAttributePoints_Implementation(int32 InAttributePoints)
{
	AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	MyPlayerState->AddAttributePoints(InAttributePoints);
}

void APlayerCharacter::AddToSpellPoints_Implementation(int32 InSpellPoints)
{
	AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	MyPlayerState->AddSpellPoints(InSpellPoints);
}

int32 APlayerCharacter::GetAttributePoints_Implementation() const
{
	AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	return MyPlayerState->GetAttributePoints();
}

int32 APlayerCharacter::GetSpellPoints_Implementation() const
{
	AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	return MyPlayerState->GetSpellPoints();
}

void APlayerCharacter::ShowMagicCircle_Implementation(UMaterialInterface* DecalMaterial)
{
	if (AMyPlayerController* KDPlayerController = Cast<AMyPlayerController>(GetController()))
	{
		KDPlayerController->ShowMagicCircle(DecalMaterial);
		KDPlayerController->bShowMouseCursor = false;
	}
}

void APlayerCharacter::HideMagicCircle_Implementation()
{
	if (AMyPlayerController* KDPlayerController = Cast<AMyPlayerController>(GetController()))
	{
		KDPlayerController->HideMagicCircle();
		KDPlayerController->bShowMouseCursor = true;
	}
}

void APlayerCharacter::SaveProgress_Implementation(const FName& CheckpointTag)
{
	AMyGameModeBase* KDGameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));

	if (KDGameMode)
	{
		ULoadScreenSaveGame* SaveData = KDGameMode->RetrieveInGameSaveData();
		if (SaveData == nullptr) return;

		SaveData->PlayerStartTag = CheckpointTag;

		if (AMyPlayerState* KDPlayerState = Cast<AMyPlayerState>(GetPlayerState()))
		{
			SaveData->PlayerLevel = KDPlayerState->GetPlayerLevel();
			SaveData->PlayerXP = KDPlayerState->GetPlayerXP();
			SaveData->AttributePoints = KDPlayerState->GetAttributePoints();
			SaveData->SpellPoints = KDPlayerState->GetSpellPoints();
		}
		SaveData->Strength = UKDAttributeSet::GetStrengthAttribute().GetNumericValue(GetAttributeSet());
		SaveData->Intelligence = UKDAttributeSet::GetIntelligenceAttribute().GetNumericValue(GetAttributeSet());
		SaveData->Resilience = UKDAttributeSet::GetResilienceAttribute().GetNumericValue(GetAttributeSet());
		SaveData->Vigor = UKDAttributeSet::GetVigorAttribute().GetNumericValue(GetAttributeSet());
		
		SaveData->bFirstTimeLoadIn = false;

		if (!HasAuthority()) return;

		UKDAbilitySystemComponent* KDASC = Cast<UKDAbilitySystemComponent>(AbilitySystemComponent);
		FForEachAbility SaveAbilityDelegate;
		SaveData->SavedAbilities.Empty();
		SaveAbilityDelegate.BindLambda
		(
			[this, KDASC, SaveData](const FGameplayAbilitySpec& AbilitySpec)
			{
				
				const FGameplayTag AbilityTag = KDASC->GetAbilityTagFromSpec(AbilitySpec);
				UAbilityInfo* AbilityInfo = UKDAbilitySystemLibrary::GetAbilityInfo(this);
				FKDAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);

				FSavedAbility SavedAbility;
				SavedAbility.GameplayAbility = Info.Ability;
				SavedAbility.AbilityLevel = AbilitySpec.Level;
				SavedAbility.AbilitySlot = KDASC->GetSlotFromAbilityTag(AbilityTag);
				SavedAbility.AbilityStatus = KDASC->GetStatusFromAbilityTag(AbilityTag);
				SavedAbility.AbilityTag = AbilityTag;
				SavedAbility.AbilityType = Info.AbilityTypeTag;

				SaveData->SavedAbilities.AddUnique(SavedAbility);
			}
		);

		KDASC->ForEachAbility(SaveAbilityDelegate);

		KDGameMode->SaveInGameProgressData(SaveData);
	}
}

void APlayerCharacter::StartInteract_Implementation(AActor* Actor)
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (AMyPlayerController* MyPC = Cast<AMyPlayerController>(PC))
		{
			MyPC->Interactable = Actor;
		}
	}
}

void APlayerCharacter::StopInteract_Implementation(AActor* Actor)
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (AMyPlayerController* MyPC = Cast<AMyPlayerController>(PC))
		{
			MyPC->Interactable = Actor;
		}
	}
}

void APlayerCharacter::CanInteract_Implementation(AActor* Actor)
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (AMyPlayerController* MyPC = Cast<AMyPlayerController>(PC))
		{
			MyPC->Interactable = Actor;
		}
	}
}

void APlayerCharacter::Interact_Implementation()
{

}

void APlayerCharacter::OnRep_Stunned()
{
	if (UKDAbilitySystemComponent* KDASC = Cast<UKDAbilitySystemComponent>(AbilitySystemComponent))
	{
		const FKDGameplayTags& GameplayTags = FKDGameplayTags::Get();
		FGameplayTagContainer BlockedTags;
		BlockedTags.AddTag(GameplayTags.Player_Block_CursorTrace);
		BlockedTags.AddTag(GameplayTags.Player_Block_InputHeld);
		BlockedTags.AddTag(GameplayTags.Player_Block_InputPressed);
		BlockedTags.AddTag(GameplayTags.Player_Block_InputReleased);
		if (bIsStunned)
		{
			KDASC->AddLooseGameplayTags(BlockedTags);
			StunDebuffComponent->Activate();
		}
		else
		{
			KDASC->RemoveLooseGameplayTags(BlockedTags);
			StunDebuffComponent->Deactivate();
		}
	}
}

void APlayerCharacter::OnRep_Burned()
{
	if (bIsBurned)
	{
		BurnDebuffComponent->Activate();
	}
	else
	{
		BurnDebuffComponent->Deactivate();
	}
}

void APlayerCharacter::InitAbilityActorInfo()
{
	AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	MyPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MyPlayerState, this);
	Cast<UKDAbilitySystemComponent>(MyPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = MyPlayerState->GetAbilitySystemComponent();
	AttributeSet = MyPlayerState->GetAttributeSet();
	OnAscRegistered.Broadcast(AbilitySystemComponent);
	AbilitySystemComponent->RegisterGameplayTagEvent(FKDGameplayTags::Get().Debuff_Stun, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &APlayerCharacter::StunTagChanged);

	if(AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()))
	{
		if (AKDHUD* KDHUD = Cast<AKDHUD>(PlayerController->GetHUD()))
		{
			KDHUD->InitOverlay(PlayerController, MyPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}

void APlayerCharacter::FireLineTrace()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT(__FUNCTION__));

	FVector Start, End;
	const float Spread = FMath::DegreesToRadians(LineTraceSpread * 0.5f);

	if (LineTraceType == ELineTraceType::CAMERA_SINGLE || LineTraceType == ELineTraceType::CAMERA_SPREAD)
	{
		// get camera point of view
		FVector CameraLocation = PlayerCamera->GetComponentLocation();
		FRotator CameraRotation = PlayerCamera->GetComponentRotation();

		Start = CameraLocation;

		if (LineTraceType == ELineTraceType::CAMERA_SPREAD)
		{
			End = CameraLocation + FMath::VRandCone(CameraRotation.Vector(), Spread, Spread) * LineTraceDistance;
		}
		else
		{
			// ending location where the camera is facing based on the line trace distance
			End = CameraLocation + (CameraRotation.Vector() * LineTraceDistance);
		}
	}
	else if (LineTraceType == ELineTraceType::PLAYER_SINGLE || LineTraceType == ELineTraceType::PLAYER_SPREAD)
	{
		// get player point of view
		FVector PlayerEyesLocation;
		FRotator PlayerEyesRotation;

		// fill in previously defined variables
		GetActorEyesViewPoint(PlayerEyesLocation, PlayerEyesRotation);

		Start = PlayerEyesLocation;
		if (LineTraceType == ELineTraceType::PLAYER_SPREAD)
		{
			End = PlayerEyesLocation + FMath::VRandCone(PlayerEyesRotation.Vector(), Spread, Spread) * LineTraceDistance;
		}
		else
		{
			End = PlayerEyesLocation + (PlayerEyesRotation.Vector() * LineTraceDistance);
		}		
	}

	FHitResult HitResult = FHitResult(ForceInit);

	FCollisionQueryParams TraceParams(FName(TEXT("LineTraceParameters")), true, NULL);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = true;

	bool bIsHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel3, TraceParams);

	if (bIsHit)
	{
		UE_LOG(LogKD, Warning, TEXT("We hit something!"));
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 5.0f, ECC_WorldStatic, 1.0f);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, HitResult.GetActor()->GetName());
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::SanitizeFloat(HitResult.Distance));
		DrawDebugBox(GetWorld(), HitResult.ImpactPoint, FVector(2.0f, 2.0f, 2.0f), FColor::Blue, false, 5.0f, ECC_WorldStatic, 1.0f);
	}
	else
	{
		UE_LOG(LogKD, Warning, TEXT("We hit nothing!"));
		DrawDebugLine(GetWorld(), Start, End, FColor::Purple, false, 5.0f, ECC_WorldStatic, 1.0f);

	}
}

void APlayerCharacter::Interact()
{
	FVector Start, End;
	FVector PlayerEyeLocation;
	FRotator PlayerEyeRotation;

	GetActorEyesViewPoint(PlayerEyeLocation, PlayerEyeRotation);
	Start = PlayerEyeLocation;
	End = PlayerEyeLocation + (PlayerEyeRotation.Vector() * LineTraceDistance);

	FCollisionQueryParams TraceParams(FName(TEXT("InteractTrace")), true, this);
	FHitResult InteractHit = FHitResult(ForceInit);

	bool bIsHit = GetWorld()->LineTraceSingleByChannel(InteractHit, Start, End, ECC_GameTraceChannel3, TraceParams);

	if (bIsHit)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 5.0f, ECC_WorldStatic, 1.0f);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, InteractHit.GetActor()->GetName());

	}
}
