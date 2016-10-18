/*=================================================
* 
* Created by: nosix1992
* Project name: MyFish
* Unreal Engine version: 4.13.0
* Created on: 2016/10/15
*
* Last Edited on: 2016/10/15
* Last Edited by: nosix1992
* 
* -------------------------------------------------
* For parts referencing UE4 code, the following copyright applies:
* Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
*
* Feel free to use this software in any commercial/free game.
* Selling this as a plugin/item, in whole or part, is not allowed.
* =================================================*/


#include "MyFish.h"
#include "Stimulus.h"
#include "Fish.h"

// Sets default values
AStimulus::AStimulus()
{
	/*CountInFish = 0.0f;*/
	PrimaryActorTick.bCanEverTick = false;
}

void AStimulus::BeginPlay()
{
	Super::BeginPlay();
	SpawnFish();
}

void AStimulus::SpawnFish()
{
	UWorld* const world = GetWorld();

	float RandomRange = 500.0f;
	float maxX = GetActorLocation().X + RandomRange;
	float maxY = GetActorLocation().Y + RandomRange;
	float maxZ = GetActorLocation().Z + RandomRange;

	float minX = GetActorLocation().X - RandomRange;
	float minY = GetActorLocation().Y - RandomRange;

	float minZ = GetActorLocation().Z - RandomRange;

	FVector spawnLoc = FVector(0, 0, 0);

	for (int i = 0; i < FishType.Num(); i++)
	{

		for (int j = 0; j < CountInFish[i]; j++)
		{
			AFish * aFish = Cast<AFish>(world->SpawnActor(FishType[i]));
			spawnLoc = FVector(FMath::FRandRange(minX, maxX), FMath::FRandRange(minY, maxY), FMath::FRandRange(minZ, maxZ));
			aFish->SetActorLocation(spawnLoc);
		}

	}
}
