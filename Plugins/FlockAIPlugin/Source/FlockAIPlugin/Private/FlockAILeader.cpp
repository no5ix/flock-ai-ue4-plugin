// Fill out your copyright notice in the Description page of Project Settings.

#include "FlockAIPlugin.h"
#include "FlockAILeader.h"


// Sets default values
AFlockAILeader::AFlockAILeader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFlockAILeader::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlockAILeader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

