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

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FishLeader.generated.h"

UCLASS()
class MYFISH_API AFishLeader : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFishLeader();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FishFlock)
		bool EnableSplineTick;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FishFlock)
		float AddLeaderTimerInterval;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FishFlock)
		float RemoveLeaderLocationInterval;


	TArray<FVector> LeaderLocation;

	void AddNextLeaderLocation();
	void RemoveLeaderLocation();
	FTimerHandle UnusedHandle;

	FVector NextLeaderLocation;
	int AddIndex;
	int RemoveIndex;

	bool isInitTimer;

};
