/*=================================================
* FileName: Stimulus.h
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

#pragma once

#include "GameFramework/Actor.h"
#include "Fish.h"
#include "Stimulus.generated.h"

UCLASS()
class MYFISH_API AStimulus : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStimulus();

	// virtual void BeginPlay() override;
	// Called every frame
	// virtual void Tick(float DeltaSeconds) override;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	// 	TArray<UClass*> FishType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
		TSubclassOf<AFish> FishType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
		int CountInFish;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
		float SpawnMaxRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
		float SpawnMinRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
		float FishLifeSpan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
		bool IsRinglike;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
		float SpawnDuration;

	UFUNCTION(BlueprintCallable, Category = Config)
	void SpawnFish();

	void SpawnFishes();

	void SpanwWanderFishesNClearTimer();
	void SpanwWanderFishes();

	void SpanwCommonFishes();
	void SpawnCommonFishesNClearTimer();

	float maxX;
	float maxY;
	float maxZ;
	float minX;
	float minY;
	float minZ;

	int count;
	FTimerHandle UnusedHandle;
	FVector spawnLoc;

	

	
};
