// Fill out your copyright notice in the Description page of Project Settings.

#include "FlockAIPlugin.h"
#include "FlockAISpawner.h"
#include "FlockAIBase.h"




AFlockAISpawner::AFlockAISpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComp"));
	SplineComp->SetupAttachment(SceneRoot);
	SplineComp->SetClosedLoop(true);

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
	Speed = 300.0f;
}

void AFlockAISpawner::BeginPlay()
{
	Super::BeginPlay();

	//MaxCanTickSerialNumber = FlockAIAmount / TickFlockAIAmountPerFrame;
	SpawnFlockAI();
	if (SplineComp->GetNumberOfSplinePoints() > 2)
	{
		FlockLeader->bIsMove = true;
	}
}

void AFlockAISpawner::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (FlockLeader)
	{
		if (FlockLeader->bIsMove)
		{
			SpeedScale = Speed / SplineComp->GetSplineLength() * DeltaSeconds;
			FVector LeaderLocation = SplineComp->GetLocationAtDistanceAlongSpline(CurrentScale * SplineComp->GetSplineLength(), ESplineCoordinateSpace::World);
			FlockLeader->SetActorLocation(LeaderLocation);
			if (CurrentScale > 1.f)
				CurrentScale = 0.0f;
			else
				CurrentScale += SpeedScale;
		}
	}
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
		if (Cast<AFlockAIMoveToLeader>(flock))
			Cast<AFlockAIMoveToLeader>(flock)->SetFlockAILeader(FlockLeader);
		UGameplayStatics::FinishSpawningActor(flock, SpawnTrans);
	}
}