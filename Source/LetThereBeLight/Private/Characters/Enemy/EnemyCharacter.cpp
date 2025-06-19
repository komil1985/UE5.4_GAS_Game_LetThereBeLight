// Copyright ASKD Games

#include "Characters/Enemy/EnemyCharacter.h"
#include "LetThereBeLight/LetThereBeLight.h"
#include "AbilitySystem/KDAbilitySystemComponent.h"
#include "AbilitySystem/KDAttributeSet.h"
#include "Components/WidgetComponent.h"
#include <UI/Widget/KDUserWidget.h>
#include <AbilitySystem/KDAbilitySystemLibrary.h>
#include "Misc/KDGameplayTags.h"
#include "AI/KDAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	BaseWalkSpeed = 300.0f;

	AbilitySystemComponent = CreateDefaultSubobject<UKDAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UKDAttributeSet>("AttributeSet");

	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	GetMesh()->MarkRenderStateDirty();
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->MarkRenderStateDirty();

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBar->SetupAttachment(RootComponent);
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	KDAIController = Cast<AKDAIController>(NewController);
	KDAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	KDAIController->RunBehaviorTree(BehaviorTree);
	KDAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	KDAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"), CharacterClass != ECharacterClass::Warrior);
}

void AEnemyCharacter::SetProgressBar()
{
	if (UKDUserWidget* UserWidget = Cast<UKDUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		UserWidget->SetWidgetController(this);
	}
}

void AEnemyCharacter::BindAndBroadcastDelegate()
{
	if (UKDAttributeSet* KDAttSet = Cast<UKDAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(KDAttSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(KDAttSet->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

		AbilitySystemComponent->RegisterGameplayTagEvent(FKDGameplayTags::Get().Effect_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&AEnemyCharacter::HitReactTagChanged
		);

		OnHealthChanged.Broadcast(KDAttSet->GetHealth());
		OnMaxHealthChanged.Broadcast(KDAttSet->GetMaxHealth());
	}
}

void AEnemyCharacter::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.0f : BaseWalkSpeed;

	if (KDAIController && KDAIController->GetBlackboardComponent())
	{
		KDAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
	}
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	check(AbilitySystemComponent);
	InitAbilityActorInfo();

	if (HasAuthority())
	{
		UKDAbilitySystemLibrary::GiveStartupAbilities(this, GetAbilitySystemComponent(), CharacterClass);
	}

	SetProgressBar();
	BindAndBroadcastDelegate();
}

void AEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UKDAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	AbilitySystemComponent->RegisterGameplayTagEvent(FKDGameplayTags::Get().Debuff_Stun, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AEnemyCharacter::StunTagChanged);

	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}
	OnAscRegistered.Broadcast(AbilitySystemComponent);
}

void AEnemyCharacter::InitializeDefaultAttributes() const
{
	UKDAbilitySystemLibrary::InitilizeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}

void AEnemyCharacter::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	Super::StunTagChanged(CallbackTag, NewCount);

	if (KDAIController && KDAIController->GetBlackboardComponent())
	{
		KDAIController->GetBlackboardComponent()->SetValueAsBool(FName("Stunned"), bIsStunned);
	}
}


void AEnemyCharacter::HighlightActor_Implementation()
{
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);	
}

void AEnemyCharacter::UnHighlightActor_Implementation()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AEnemyCharacter::SetMoveToLocation_Implementation(FVector& OutDestination)
{
	// Do not change OutDestination //
}

int32 AEnemyCharacter::GetPlayerLevel_Implementation()
{
	return Level;
}

void AEnemyCharacter::Die(const FVector& DeathImpulse)
{
	SetLifeSpan(LifeSpan);
	//PlayAnimMontage(GetDieMontage(), 1.0f);
	if (KDAIController) KDAIController->GetBlackboardComponent()->SetValueAsBool(FName("Dead"), true);
	SpawnLoot();
	Super::Die(DeathImpulse);

	//AController* NewController = GetController();
	//KDAIController = Cast<AKDAIController>(NewController);
	//KDAIController->Destroy();
}

void AEnemyCharacter::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* AEnemyCharacter::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}
