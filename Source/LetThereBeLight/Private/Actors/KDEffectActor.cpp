// Copyright ASKD Games


#include "Actors/KDEffectActor.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/KDAttributeSet.h"

AKDEffectActor::AKDEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(Mesh);
}

void AKDEffectActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: Change this to apply Gameplay Effect. For now using const_cast as a Hack!
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UKDAttributeSet* AttributeSet = Cast<UKDAttributeSet>
		(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UKDAttributeSet::StaticClass()));

		UKDAttributeSet* MutableAttributeSet = const_cast<UKDAttributeSet*>(AttributeSet);
		MutableAttributeSet->SetHealth(AttributeSet->GetHealth() + 25.0f);
		MutableAttributeSet->SetMana(AttributeSet->GetMana() - 25.0f);
		Destroy();
	}
}

void AKDEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* otherComp, int32 OtherBodyIndex)
{

}

void AKDEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AKDEffectActor::BeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AKDEffectActor::EndOverlap);

}

