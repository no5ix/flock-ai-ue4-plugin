// Fill out your copyright notice in the Description page of Project Settings.

#include "FlockAIPlugin.h"
#include "FlockAISpawner.h"
#include "FlockAIBase.h"




AFlockAISpawner::AFlockAISpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnRangeMaxX = 0.f;
	SpawnRangeMaxY = 0.f;
	SpawnRangeMaxZ = 0.f;

	SpawnRangeMinX = 0.f;
	SpawnRangeMinY = 0.f;
	SpawnRangeMinZ = 0.f;

	SpawnMaxRange = 500;
	SpawnMinRange = 200;

	CurrentFlockAICount = 0;

	CanTickSerialNumber = 0;
	MaxCanTickSerialNumber = 0;

	TickFlockAIAmountPerFrame = 100;

	SpawnTrans = FTransform();

}

void AFlockAISpawner::BeginPlay()
{
	Super::BeginPlay();

	//MaxCanTickSerialNumber = FlockAIAmount / TickFlockAIAmountPerFrame;
	SpawnFlockAI();
}

void AFlockAISpawner::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (FlockAIAmount > 0)
	{
		if (++CanTickSerialNumber > MaxCanTickSerialNumber)
		{
			CanTickSerialNumber = 0;
		}
	}
}

bool AFlockAISpawner::CanProcessTick(uint32 FlockAISerialNum) const
{
	if (FlockAISerialNum == CanTickSerialNumber)
	{
		return true;
	}
	return false;
}

void AFlockAISpawner::SpawnFlockAI_Implementation()
{

	if (FlockAIAmount > 0 && FlockAIType)
	{

		MaxCanTickSerialNumber = FlockAIAmount / TickFlockAIAmountPerFrame;

		SpawnRangeMaxX = GetActorLocation().X + SpawnMaxRange;
		SpawnRangeMaxY = GetActorLocation().Y + SpawnMaxRange;
		SpawnRangeMaxZ = GetActorLocation().Z + SpawnMaxRange;

		SpawnRangeMinX = GetActorLocation().X + SpawnMinRange;
		SpawnRangeMinY = GetActorLocation().Y + SpawnMinRange;
		SpawnRangeMinZ = GetActorLocation().Z + SpawnMinRange;

		if (SpawnDuration > 1)
		{
			GetWorldTimerManager().SetTimer(SpawnFlockAITimeHandle, this, &AFlockAISpawner::LoopSpawn, SpawnDuration / FlockAIAmount, true);
		}
		else
		{
			for (int i = 0; i < FlockAIAmount; i++)
			{
				DoSpawnFlockAI();
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString("Warning!! A BP_Spawner FlockAIType is EMPTY OR FlockAIAmount is invalid !"));
		return;
	}
}

void AFlockAISpawner::LoopSpawn()
{
	DoSpawnFlockAI();
	if (CurrentFlockAICount == FlockAIAmount)
	{
		GetWorldTimerManager().ClearTimer(SpawnFlockAITimeHandle);
	}
}

void AFlockAISpawner::DoSpawnFlockAI()
{
	SpawnTrans = FTransform(FVector(FMath::FRandRange(SpawnRangeMinX, SpawnRangeMaxX), FMath::FRandRange(SpawnRangeMinY, SpawnRangeMaxY), FMath::FRandRange(SpawnRangeMinZ, SpawnRangeMaxZ)));

	AFlockAIBase *flock = Cast<AFlockAIBase>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, FlockAIType, SpawnTrans));
	if (flock)
	{
		flock->SetLifeSpan(FlockAILifeSpan);
		flock->SetFlockAISpawner(this);
		flock->SetFlockAISerialNumber( (++CurrentFlockAICount) / TickFlockAIAmountPerFrame );
		UGameplayStatics::FinishSpawningActor(flock, SpawnTrans);
	}
}