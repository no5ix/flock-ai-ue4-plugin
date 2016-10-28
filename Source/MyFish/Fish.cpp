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

#include "MyFish.h"
#include "Fish.h"
#include "Stimulus.h"
#include "FishLeader.h"
#include "CheckFishCharacter.h"
// #include "WidgetLayoutLibrary.h"


// Sets default values
AFish::AFish()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.03f;

	IsSetSpawnLocation= false;
	IsAlreadyWander = false;
	SpawnLocation = FVector(0, 0, 0);
	WanderRangeX = 30000.0f;
	WanderRangeY = 30000.0f;
	WanderRangeZ = 30000.0f;
	DestLocation = FVector(0, 0, 0);

	ScreenMaxX = 1920.0f;
	ScreenMaxY = 1080.0f;
	ScreenMinX = 0.0f;
	ScreenMinY = 0.0f;

	BaseMovementSpeed = 150.0f;
	MaxMovementSpeed = 600.0f;
	distBehindSpeedUpRange = 1000.0f;
	SeparationWeight = 2.2f;


	EnemyWeight = 1400.0f;
	AgentPhysicalRadius = 45.0f;
	TurnSpeed = 1.0f;
	CurrentMovementSpeed = BaseMovementSpeed;

	SeparationComponent = FVector(0, 0, 0);
	EnemyComponent = FVector(0, 0, 0);

	FollowLeaderComponent = FVector(0, 0, 0);
	FollowLeaderWeight = 5.0f;

	IsSetLeaderUp = false;
	IsGetGameViewportSize = false;

	IsHasEnemy = false;

	isAtCenter = false;

	SmallSphereRadius = 10.0f;
	SmallSphereLocation = FVector(25.0f, 0, 0.0f);

	MiddleSphereRadius = 20.0f;
	MiddleSphereLocation = FVector(20.0f, 0, 15.0f);

	CheckEnemySmallSphereRadius = 75.0f;
	CheckEnemySmallSphereLocation = FVector(0.0f, 0, 0);

	CheckEnemyMiddleSphereRadius = 75.0f;
	CheckEnemyMiddleSphereLocation = FVector(0.0f, 0, 0);

	LargeSphereRadius = 45.0f;

	CurrentSphereRadius = SmallSphereRadius;

	CurrentFishLocation = FVector(0, 0, 0);
	SpecificNeighborLocation = FVector(0, 0, 0);
	NeighbourhoodNum = 0.0f;

	NewMoveVector = FVector(0, 0, 0);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = MeshComponent;
	MeshComponent->CastShadow = false;
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	CheckSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CheckSphere"));
	CheckSphere->AttachTo(RootComponent);
	CheckSphere->SetSphereRadius(SmallSphereRadius);

}

// Called when the game starts or when spawned
void AFish::BeginPlay()
{
	Super::BeginPlay();

	MyPawn = Cast<ACheckFishCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	PController = GetWorld()->GetFirstPlayerController();
	NewMoveVector = GetActorRotation().Vector().GetSafeNormal();

}

// Called every frame
void AFish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetLeader();

	SetSpawnLocation();

	GetGameViewportSizeUntilGet();
	if (IsGetGameViewportSize)
	{
		ResetComponents();
		CalculateFlockNewMoveVector(DeltaTime);

	}
}

void AFish::SetSpawnLocation()
{
	if (!IsSetSpawnLocation)
	{

		SpawnLocation = GetActorLocation();	
		if (SpawnLocation.X != 0 && SpawnLocation.Y != 0 && SpawnLocation.Z != 0)
		{
			IsSetSpawnLocation = true;
		}
		// GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::SanitizeFloat(SpawnLocation.X));
		// GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::SanitizeFloat(SpawnLocation.Y));
		// GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::SanitizeFloat(SpawnLocation.Z));
	}
}

void AFish::UpdateTickIntervalAndCheckSphereRadius(bool _IsHasEnemy, FVector _CurrentFishLocation)
{
	UGameplayStatics::ProjectWorldToScreen(PController, _CurrentFishLocation, ScreenPosition);

	DistanceToPawn = (MyPawn->CameraCpp->GetComponentLocation() - _CurrentFishLocation).Size();
	if (DistanceToPawn > 2000.0f)
	{
		if (ScreenPosition.X <= ScreenSecondMaxX && ScreenPosition.X >= ScreenSecondMinX && ScreenPosition.Y <= ScreenSecondMaxY && ScreenPosition.Y >= ScreenSecondMinY)
		{
			if (DistanceToPawn > 8000.0f)
			{

				if (ScreenPosition.X <= ScreenCenterMaxX && ScreenPosition.X >= ScreenCenterMinX && ScreenPosition.Y <= ScreenCenterMaxY && ScreenPosition.Y >= ScreenCenterMinY)
				{
					PrimaryActorTick.TickInterval = 0.1f;
					isAtCenter = true;
				}
				else
				{

					PrimaryActorTick.TickInterval = 0.12f;
				}

			}
			else if (DistanceToPawn <= 8000.0f && DistanceToPawn > 7000.0f)
			{

				if (ScreenPosition.X <= ScreenCenterMaxX && ScreenPosition.X >= ScreenCenterMinX && ScreenPosition.Y <= ScreenCenterMaxY && ScreenPosition.Y >= ScreenCenterMinY)
				{
					PrimaryActorTick.TickInterval = 0.09f;

					isAtCenter = true;
				}
				else
				{

					PrimaryActorTick.TickInterval = 0.11f;
				}
			}
			else if (DistanceToPawn <= 7000.0f && DistanceToPawn > 6000.0f)
			{

				if (ScreenPosition.X <= ScreenCenterMaxX && ScreenPosition.X >= ScreenCenterMinX && ScreenPosition.Y <= ScreenCenterMaxY && ScreenPosition.Y >= ScreenCenterMinY)
				{
					PrimaryActorTick.TickInterval = 0.08f;

					isAtCenter = true;
				}
				else
				{

					PrimaryActorTick.TickInterval = 0.1f;
				}
			}
			else if (DistanceToPawn <= 6000.0f && DistanceToPawn > 5000.0f)
			{

				if (ScreenPosition.X <= ScreenCenterMaxX && ScreenPosition.X >= ScreenCenterMinX && ScreenPosition.Y <= ScreenCenterMaxY && ScreenPosition.Y >= ScreenCenterMinY)
				{
					PrimaryActorTick.TickInterval = 0.07f;

					isAtCenter = true;
				}
				else
				{

					PrimaryActorTick.TickInterval = 0.09f;
				}
			}

			else if (DistanceToPawn <= 5000.0f && DistanceToPawn > 4000.0f)
			{
				if (ScreenPosition.X <= ScreenCenterMaxX && ScreenPosition.X >= ScreenCenterMinX && ScreenPosition.Y <= ScreenCenterMaxY && ScreenPosition.Y >= ScreenCenterMinY)
				{
					PrimaryActorTick.TickInterval = 0.06f;

					isAtCenter = true;
				}
				else
				{

					PrimaryActorTick.TickInterval = 0.08f;
				}
			}
			else if (DistanceToPawn <= 4000.0f && DistanceToPawn > 3000.0f)
			{

				if (ScreenPosition.X <= ScreenCenterMaxX && ScreenPosition.X >= ScreenCenterMinX && ScreenPosition.Y <= ScreenCenterMaxY && ScreenPosition.Y >= ScreenCenterMinY)
				{
					PrimaryActorTick.TickInterval = 0.045f;

					isAtCenter = true;
				}
				else
				{

					PrimaryActorTick.TickInterval = 0.05f;
				}
			}
			else if (DistanceToPawn <= 3000.0f && DistanceToPawn > 2000.0f)
			{


				if (ScreenPosition.X <= ScreenCenterMaxX && ScreenPosition.X >= ScreenCenterMinX && ScreenPosition.Y <= ScreenCenterMaxY && ScreenPosition.Y >= ScreenCenterMinY)
				{
					PrimaryActorTick.TickInterval = 0.03f;

					isAtCenter = true;
				}
				else
				{

					PrimaryActorTick.TickInterval = 0.035f;
				}
			}
			if (!isAtCenter)
			{
				if (MyPawn->SumNearbyFish < 20.0f)
				{

					if (CurrentSphereRadius != SmallSphereRadius)
					{
						CheckSphere->SetSphereRadius(SmallSphereRadius);
						CurrentSphereRadius = SmallSphereRadius;
						CheckSphere->SetRelativeLocation(SmallSphereLocation);
					}
				}
				else if (MyPawn->SumNearbyFish >= 20.0f && MyPawn->SumNearbyFish < 50.0f)
				{

					PrimaryActorTick.TickInterval += 0.05f;

					if (CurrentSphereRadius != 15.0f)
					{
						CheckSphere->SetSphereRadius(15.0f);
						CurrentSphereRadius = 15.0f;
						CheckSphere->SetRelativeLocation(FVector(50.0f, 0.0f, 15.0f));
					}
				}
				else if (MyPawn->SumNearbyFish >= 50.0f)
				{

					PrimaryActorTick.TickInterval += 0.1f;

					if (CurrentSphereRadius != 7.5f)
					{
						CheckSphere->SetSphereRadius(7.5f);
						CurrentSphereRadius = 7.5f;
						CheckSphere->SetRelativeLocation(FVector(45.0f, 0.0f, 15.0f));
					}
				}
			}

		}
		else
		{


			if (CurrentSphereRadius != SmallSphereRadius)
			{
				CheckSphere->SetSphereRadius(SmallSphereRadius);
				CurrentSphereRadius = SmallSphereRadius;
				CheckSphere->SetRelativeLocation(SmallSphereLocation);
			}

			if (DistanceToPawn > 8000.0f)
			{

				PrimaryActorTick.TickInterval = 0.13f;
			}
			else if (DistanceToPawn <= 8000.0f && DistanceToPawn > 7000.0f)
			{

				PrimaryActorTick.TickInterval = 0.12f;

			}
			else if (DistanceToPawn <= 7000.0f && DistanceToPawn > 6000.0f)
			{

				PrimaryActorTick.TickInterval = 0.1f;

			}
			else if (DistanceToPawn <= 6000.0f && DistanceToPawn > 5000.0f)
			{

				PrimaryActorTick.TickInterval = 0.14f;

			}
			else if (DistanceToPawn <= 5000.0f && DistanceToPawn > 4000.0f)
			{

				PrimaryActorTick.TickInterval = 0.12f;

			}
			else if (DistanceToPawn <= 4000.0f && DistanceToPawn > 3000.0f)
			{

				PrimaryActorTick.TickInterval = 0.1f;

			}
		}


	}
	else
	{

		if (ScreenPosition.X <= ScreenMaxX && ScreenPosition.X >= ScreenMinX && ScreenPosition.Y <= ScreenMaxY && ScreenPosition.Y >= ScreenMinY)
		{

			if (DistanceToPawn <= 500.0f)
			{

				if (CurrentSphereRadius != LargeSphereRadius)
				{
					CheckSphere->SetSphereRadius(LargeSphereRadius);
					CurrentSphereRadius = LargeSphereRadius;
					CheckSphere->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
				}
				PrimaryActorTick.TickInterval = 0.005f;
			}
			else
			{

				if (DistanceToPawn <= 2000.0f && DistanceToPawn > 1000.0f)
				{

					PrimaryActorTick.TickInterval = 0.015f;
				}
				else if (DistanceToPawn <= 1000.0f && DistanceToPawn > 500.0f)
				{
					PrimaryActorTick.TickInterval = 0.01f;
				}

				if (CurrentSphereRadius != MiddleSphereRadius)
				{
					CheckSphere->SetSphereRadius(MiddleSphereRadius);
					CurrentSphereRadius = MiddleSphereRadius;
					CheckSphere->SetRelativeLocation(MiddleSphereLocation);
				}



				if (_IsHasEnemy)
				{

					PrimaryActorTick.TickInterval -= 0.005f;
				}

			}
		}
		else
		{

			if (DistanceToPawn <= 500.0f)
			{
				PrimaryActorTick.TickInterval = 0.001f;
			}
			else
			{
				PrimaryActorTick.TickInterval = 0.1f;
			}


			if (CurrentSphereRadius != SmallSphereRadius)
			{
				CheckSphere->SetSphereRadius(SmallSphereRadius);
				CurrentSphereRadius = SmallSphereRadius;
				CheckSphere->SetRelativeLocation(SmallSphereLocation);
			}
		}

	}
}

void AFish::ResetComponents()
{

	SeparationComponent = FVector(0, 0, 0);
	EnemyComponent = FVector(0, 0, 0);
	FollowLeaderComponent = FVector(0, 0, 0);
	IsHasEnemy = false;
	isAtCenter = false;
}

void AFish::SetLeader()
{
	if (!IsSetLeaderUp)
	{
		TArray<AActor*> aFishLeaderList;
		UGameplayStatics::GetAllActorsOfClass(this, LeaderClass, aFishLeaderList);
		if (aFishLeaderList.Num())
		{
			Leader = aFishLeaderList[0];
			IsSetLeaderUp = true;
		}
	}

}

void AFish::GetGameViewportSizeUntilGet()
{
	if (!IsGetGameViewportSize)
	{


		FVector2D GameViewportSize = GetGameViewportSize();
		if (GameViewportSize.X != 0.0f && GameViewportSize.Y != 0.0f)
		{

			GameViewportSizeX = GameViewportSize.X;
			GameViewportSizeY = GameViewportSize.Y;


			ScreenMaxX = GameViewportSizeX + 1000.0f;

			ScreenMaxY = GameViewportSizeY + 1000.0f;

			ScreenMinX = -1000.0f;

			ScreenMinY = -1000.0f;


			ScreenSecondMaxX = ScreenMaxX;

			ScreenSecondMaxY = ScreenMaxY;

			ScreenSecondMinX = ScreenMinX;

			ScreenSecondMinY = ScreenMinY;


			// ScreenSecondMaxX = GameViewportSizeX + 500.0f;

			// ScreenSecondMaxY = GameViewportSizeY + 500.0f;

			// ScreenSecondMinX = -500.0f;

			// ScreenSecondMinY = -500.0f;


			ScreenCenterMaxX = GameViewportSizeX / 6.0f * 5.0f;

			ScreenCenterMaxY = GameViewportSizeY / 6.0f * 5.0f;

			ScreenCenterMinX = GameViewportSizeX / 6.0f;

			ScreenCenterMinY = GameViewportSizeY / 6.0f;

			IsGetGameViewportSize = true;
		}
		/* GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::SanitizeFloat(GameViewportSize.X));
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::SanitizeFloat(GameViewportSize.Y));*/
	}

}


void AFish::CalculateFlockNewMoveVector(float DeltaTime)
{
	CurrentFishLocation = GetActorLocation();

	//Maintain distance behind Leader
	if (this->Leader)
	{

		// Calculate all seperation and distance behind leader into one vector
		DestLocation = this->Leader->GetActorLocation();

		if (this->GetDistanceTo(this->Leader) > this->distBehindSpeedUpRange)
		{
			// Set Speed
			this->CurrentMovementSpeed = FMath::Lerp(this->CurrentMovementSpeed, this->MaxMovementSpeed, DeltaTime);

		}
		else
		{
			// Set Speed
			this->CurrentMovementSpeed = FMath::Lerp(this->CurrentMovementSpeed, this->BaseMovementSpeed, DeltaTime);
		}
	}
	else
	{
		if (!IsAlreadyWander)
		{
			// GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString("xixi"));
			ModifyDestInterval = FMath::FRandRange(MinModifyDestInterval, MaxModifyDestInterval);
			// GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::SanitizeFloat(ModifyDestInterval));
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &AFish::SetDestLocationNSpeed, ModifyDestInterval, true);
			IsAlreadyWander = true;
		}
	}
		
	FollowLeaderComponent = 
		//distBehind + 
		DestLocation -
		CurrentFishLocation;
	FollowLeaderComponent.Normalize();

	CheckSphere->GetOverlappingActors(Neighbourhood);


	NeighbourhoodNum = Neighbourhood.Num();
	for (int i = 0; i < NeighbourhoodNum; i++)
	{
		SpecificNeighborLocation = Neighbourhood[i]->GetActorLocation();
		if (Cast<AStimulus>(Neighbourhood[i]))
		{
			ResetComponents();
			EnemyComponent = CurrentFishLocation - SpecificNeighborLocation;

			IsHasEnemy = true;

			break;

		}

		if (Cast<AFish>(Neighbourhood[i]))
		{
			if (Neighbourhood[i] != this)
			{
				temp_vector = CurrentFishLocation - SpecificNeighborLocation;
				temp_vector.Normalize();
				SeparationComponent += temp_vector / FMath::Abs((CurrentFishLocation - SpecificNeighborLocation).Size() - (AgentPhysicalRadius * 2));
			}

		}


	}

	UpdateTickIntervalAndCheckSphereRadius(IsHasEnemy, CurrentFishLocation);


	if (IsHasEnemy == false && NeighbourhoodNum > 0)
	{
		SeparationComponent = (SeparationComponent * 100.0f * (5.0f / (float)NeighbourhoodNum)) + SeparationComponent * 100;
	}


	NewMoveVector =
		SeparationComponent * SeparationWeight +
		EnemyComponent * EnemyWeight +
		FollowLeaderComponent * FollowLeaderWeight;
	// Set Rotation
	NewRotation = NewMoveVector.Rotation();
	NewRotation = FMath::RInterpTo(this->GetActorRotation(), NewRotation, DeltaTime, this->TurnSpeed);

	this->SetActorRotation(NewRotation);
	// Set Velocity
	NewDirection = this->GetActorForwardVector() * (DeltaTime * this->CurrentMovementSpeed);

	this->AddActorWorldOffset(NewDirection);
}

FVector2D AFish::GetGameViewportSize()
{
	FVector2D Result = FVector2D(1, 1);

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize( /*out*/Result);
	}

	return Result;

	/*UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	if (World && World->IsGameWorld())
	{
	if (UGameViewportClient* ViewportClient = World->GetGameViewport())
	{
	FVector2D ViewportSize;
	ViewportClient->GetViewportSize(ViewportSize);
	return ViewportSize;
	}
	}

	return FVector2D(1, 1);*/
}

FVector2D AFish::GetGameResolution()
{
	FVector2D Result = FVector2D(1, 1);

	Result.X = GSystemResolution.ResX;
	Result.Y = GSystemResolution.ResY;

	return Result;
}

void AFish::SetDestLocationNSpeed()
{
	if (FMath::RandRange(1, 2) == 1)
	{
		// Set Speed
		this->CurrentMovementSpeed = FMath::Lerp(this->CurrentMovementSpeed, this->MaxMovementSpeed, 0.05);

	}
	else
	{
		// Set Speed
		this->CurrentMovementSpeed = FMath::Lerp(this->CurrentMovementSpeed, this->BaseMovementSpeed, 0.1);
	}
	DestLocation = FVector(
		FMath::FRandRange(SpawnLocation.X-WanderRangeX, SpawnLocation.X+WanderRangeX), 
		FMath::FRandRange(SpawnLocation.Y-WanderRangeY, SpawnLocation.Y+WanderRangeY), 
		FMath::FRandRange(SpawnLocation.Z-WanderRangeZ, SpawnLocation.Z+WanderRangeZ)
	);
}