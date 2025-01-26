// Copyright ASKD Games


#include "AbilitySystem/Abilities/KDSummonAbility.h"

TArray<FVector> UKDSummonAbility::GetSpawnLocation()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnRadius / NumMinions;

	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnRadius / 2.0f, FVector::UpVector);
	TArray<FVector> SpawnLocations;
	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		FVector RandomSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);

		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, RandomSpawnLocation + FVector(0.0f, 0.0f, 400.0f), RandomSpawnLocation - FVector(0.0f, 0.0f, 400.0f), ECC_Visibility);
		if (Hit.bBlockingHit)
		{
			RandomSpawnLocation = Hit.ImpactPoint;
		}
		SpawnLocations.Add(RandomSpawnLocation);
	}

	return SpawnLocations;
}

TSubclassOf<APawn> UKDSummonAbility::GetRandomMinionClass()
{
	const int32 Selection = FMath::RandRange(0, MinionClasses.Num() - 1);
	return MinionClasses[Selection];
}