// Copyright ASKD Games


#include "Actors/KDInfoActorBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "Interactions/PlayerInterface.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"


AKDInfoActorBase::AKDInfoActorBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(Mesh);
	Widget->SetVisibility(false);

	DisplayedWidget = CreateDefaultSubobject<UUserWidget>(TEXT("DisplayedWidget"));
	
}

void AKDInfoActorBase::BeginPlay()
{
	Super::BeginPlay();

}

void AKDInfoActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKDInfoActorBase::CanInteract_Implementation()
{
	if (IsValid(Widget))
	{
		Widget->SetVisibility(true);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Can_Interface Activated"));
	}
}

void AKDInfoActorBase::StartInteract_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Start_Interface Activated"));
}

void AKDInfoActorBase::StopInteract_Implementation()
{
	if (IsValid(Widget) && IsValid(DisplayedWidget))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Stop_Interface Activated"));
		Widget->SetVisibility(false);
		DisplayedWidget->SetVisibility(ESlateVisibility::Hidden);
		TextToDisplay = 0;
	}
}

void AKDInfoActorBase::Interact_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Interact_Interface Activated"));
	if (IsValid(DisplayedWidget) && IsValid(Widget))
	{
		DisplayedWidget->SetVisibility(ESlateVisibility::Visible);
		DisplayedWidget->AddToViewport(0);
		Widget->SetVisibility(false);
		TextToDisplay = 1;
	}	
}
