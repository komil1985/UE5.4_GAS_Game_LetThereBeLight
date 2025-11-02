// Copyright ASKD Games

#include "Characters/NPC/NPCCharacter.h"
#include "Components/WidgetComponent.h"
#include "Components/MounteaDialogueParticipant.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include <Characters/Player/PlayerCharacter.h>


ANPCCharacter::ANPCCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	PromptWidget = CreateDefaultSubobject<UWidgetComponent>("PromptWidget");
	PromptWidget->SetupAttachment(RootComponent);
	PromptWidget->SetVisibility(true);

	DialogueParticipant = CreateDefaultSubobject<UMounteaDialogueParticipant>("Dialogue Participant");
	
	ProximityBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProximityBox"));
	ProximityBox->SetupAttachment(RootComponent);
	ProximityBox->SetBoxExtent(FVector(200.0f));
	ProximityBox->SetCollisionProfileName(TEXT("Trigger"));
	ProximityBox->SetGenerateOverlapEvents(true);

}


void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();

	ProximityBox->OnComponentBeginOverlap.AddDynamic(this, &ANPCCharacter::OnProxomityBoxOverlapBegin);
	ProximityBox->OnComponentEndOverlap.AddDynamic(this, &ANPCCharacter::OnProximityBoxOverlapEnd);

}

void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (OverlappingPlayer.IsValid())
	{
		FVector NPCPos = GetActorLocation();
		FVector PlayerPos = OverlappingPlayer->GetActorLocation();

		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(NPCPos, PlayerPos);

		//float RelativeYaw = LookAtRotation.Yaw + GetActorRotation().Yaw;
		FRotator TargetMeshRotation(0.f, LookAtRotation.Yaw, 0.f);

		FRotator CurrentRotation = GetMesh()->GetRelativeRotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetMeshRotation, DeltaTime, MeshRotationInterpSpeed);

		GetMesh()->SetRelativeRotation(NewRotation);
	}
}

void ANPCCharacter::OnProxomityBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;

	APlayerCharacter* PlayerChar = Cast<APlayerCharacter>(OtherActor);
	if (PlayerChar && PlayerChar->IsPlayerControlled())
	{
		OverlappingPlayer = PlayerChar;
	}
}

void ANPCCharacter::OnProximityBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* PlayerChar = Cast<APlayerCharacter>(OtherActor);
	if (OverlappingPlayer == PlayerChar)
	{
		OverlappingPlayer = nullptr;
	}
}

void ANPCCharacter::CanInteract_Implementation()
{
	if (IsValid(PromptWidget))
	{
		PromptWidget->SetVisibility(false);
	}
}

void ANPCCharacter::StopInteract_Implementation()
{
	if (IsValid(PromptWidget))
	{
		PromptWidget->SetVisibility(true);
	}
}

void ANPCCharacter::Interact_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Interact_Interface Activated"));
	if (IsValid(PromptWidget))
	{
		PromptWidget->SetVisibility(false);
	}
}

void ANPCCharacter::StartDialogue_Implementation(AActor* InstigatorActor)
{
	if (IsValid(DialogueParticipant))
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Blue, "Dialogue Started");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Blue, "Dialogue Manager not initialized");
	}
}