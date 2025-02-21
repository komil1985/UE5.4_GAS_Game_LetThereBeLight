// Copyright ASKD Games


#include "Characters/Player/PlayerCharacter.h"
#include "Characters/Player/MyPlayerState.h"
#include "AbilitySystem/KDAbilitySystemComponent.h"
#include "AbilitySystem/KDAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/HUD/KDHUD.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystem/Data/LevelUpInfo.h"


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1000.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CharacterClass = ECharacterClass::Elementalist;
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init Ability actor info for the server
	InitAbilityActorInfo();
	AddCharacterAbilities();

}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init Ability actor info for the client
	InitAbilityActorInfo();

}

void APlayerCharacter::Die()
{
	SetLifeSpan(LifeSpan);
	PlayAnimMontage(GetDieMontage(), 1.0f);
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	PlayerController->DisableInput(PlayerController);
	Super::Die();
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
	AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
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
}

void APlayerCharacter::AddToAttributePoints_Implementation(int32 InAttributePoints)
{
	//AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	//check(MyPlayerState);
}

void APlayerCharacter::AddToSpellPoints_Implementation(int32 InSpellPoints)
{
	//AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	//check(MyPlayerState);
}

void APlayerCharacter::InitAbilityActorInfo()
{
	AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	MyPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MyPlayerState, this);
	Cast<UKDAbilitySystemComponent>(MyPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = MyPlayerState->GetAbilitySystemComponent();
	AttributeSet = MyPlayerState->GetAttributeSet();

	if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (AKDHUD* KDHUD = Cast<AKDHUD>(PlayerController->GetHUD()))
		{
			KDHUD->InitOverlay(PlayerController, MyPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}

