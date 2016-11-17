// // Fill out your copyright notice in the Description page of Project Settings.

// #include "OceanProject.h"
// #include "Stimulus.h"


// // Sets default values
// AStimulus::AStimulus()
// {
//  	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
// 	PrimaryActorTick.bCanEverTick = true;

// }

// // Called when the game starts or when spawned
// void AStimulus::BeginPlay()
// {
// 	Super::BeginPlay();
	
// }

// // Called every frame
// void AStimulus::Tick( float DeltaTime )
// {
// 	Super::Tick( DeltaTime );

// }

// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFish.h"
#include "Stimulus.h"
#include "Fish.h"


// Sets default values
AStimulus::AStimulus()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawnMaxRange = 500.0f;
	SpawnMinRange = -500.0f;
	IsRinglike = false;
	FishLifeSpan = 0.0f;
	SpawnDuration = 0;
	CountInFish = 0;

	maxX = 0.0f;
	maxY = 0.0f;
	maxZ = 0.0f;
	minX = 0.0f;
	minY = 0.0f;
	minZ = 0.0f;

	count = 0;
	spawnLoc = FVector(0, 0, 0);
	
	
}

// void AStimulus::BeginPlay()
// {
// 	Super::BeginPlay();
// 	// SpawnFish();
// }

void AStimulus::SpawnFish()
{
	if (CountInFish > 0 && FishType)
	{
		if (IsRinglike)
		{
			if (SpawnMaxRange < 0)
				SpawnMaxRange *= -1;
			if (SpawnMinRange < 0)
				SpawnMinRange *= -1;

			if (SpawnDuration > 1)
			{
				GetWorldTimerManager().SetTimer(UnusedHandle, this, &AStimulus::SpanwWanderFishesNClearTimer, SpawnDuration / CountInFish, true);
			}
			else
			{
				for(int i = 0; i < CountInFish; i++)
				{
					SpanwWanderFishes();
				}
			}
		}
		else
		{
			maxX = GetActorLocation().X + SpawnMaxRange;
			maxY = GetActorLocation().Y + SpawnMaxRange;
			maxZ = GetActorLocation().Z + SpawnMaxRange;

			minX = GetActorLocation().X + SpawnMinRange;
			minY = GetActorLocation().Y + SpawnMinRange;
			minZ = GetActorLocation().Z + SpawnMinRange;
			if (SpawnDuration > 1)
			{
				GetWorldTimerManager().SetTimer(UnusedHandle, this, &AStimulus::SpawnCommonFishesNClearTimer, SpawnDuration / CountInFish, true);
			}
			else
			{
				for(int i = 0; i < CountInFish; i++)
				{
					SpanwCommonFishes();
				}
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString("Warning!! A BP_Spawner FishType is EMPTY OR CountInFish is invalid !"));
		return;
	}
		
}

void AStimulus::SpawnCommonFishesNClearTimer()
{

	SpanwCommonFishes();
	count++;
	if (count == CountInFish)
		GetWorldTimerManager().ClearTimer(UnusedHandle);

}

void AStimulus::SpanwCommonFishes()
{
	DoSpawnFishes();
}

void AStimulus::SpanwWanderFishes()
{
	int RandNum = 1;
	RandNum = FMath::RandRange(1, 4);
	switch(RandNum)
	{
		case 1:
			maxX = GetActorLocation().X + SpawnMaxRange;
			minX = GetActorLocation().X + SpawnMinRange;
			maxY = GetActorLocation().Y + SpawnMaxRange;
			minY = GetActorLocation().Y - SpawnMaxRange;
			break;
		case 2:
			maxX = GetActorLocation().X - SpawnMaxRange;
			minX = GetActorLocation().X - SpawnMinRange;
			maxY = GetActorLocation().Y + SpawnMaxRange;
			minY = GetActorLocation().Y - SpawnMaxRange;
			break;
		case 3:
			maxY = GetActorLocation().Y + SpawnMaxRange;
			minY = GetActorLocation().Y + SpawnMinRange;
			maxX = GetActorLocation().X + SpawnMaxRange;
			minX = GetActorLocation().X - SpawnMaxRange;
			break;
		case 4:
			maxY = GetActorLocation().Y - SpawnMaxRange;
			minY = GetActorLocation().Y - SpawnMinRange;
			maxX = GetActorLocation().X + SpawnMaxRange;
			minX = GetActorLocation().X - SpawnMaxRange;
			break;
	}
	maxZ = GetActorLocation().Z + SpawnMaxRange;
	minZ = GetActorLocation().Z + SpawnMinRange;
	DoSpawnFishes();
}

void AStimulus::DoSpawnFishes()
{
	
	AFish * aFish = Cast<AFish>(GetWorld()->SpawnActor(FishType));
	aFish->SetLifeSpan(FishLifeSpan);
	spawnLoc = FVector(FMath::FRandRange(minX, maxX), FMath::FRandRange(minY, maxY), FMath::FRandRange(minZ, maxZ));
	aFish->SetActorLocation(spawnLoc);
}

void AStimulus::SpanwWanderFishesNClearTimer()
{

	SpanwWanderFishes();
	count++;
	if (count == CountInFish)
		GetWorldTimerManager().ClearTimer(UnusedHandle);

}
