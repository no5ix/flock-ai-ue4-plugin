/*=================================================
* 
* Created by: nosix1992
* Project name: MyFish
* Unreal Engine version: 4.13.0
* Created on: 2016/10/15
*
* Last Edited on: 2016/10/17
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

#include "MyFish.h"
#include "FishLeader.h"


// Sets default values
AFishLeader::AFishLeader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	EnableSplineTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeaderFish"));
	RootComponent = MeshComponent;
}

void AFishLeader::BeginPlay()
{
	MeshComponent->SetVisibility(false);
}