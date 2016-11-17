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
#pragma once

#include "CheckFishCharacter.h"
#include "GameFramework/Actor.h"
#include "FishLeader.h"
#include "Fish.generated.h"

UENUM()
namespace FishMoveMode
{
	enum Type
	{
		Common,
		StrictFollowLeaderPath,
		Wander,
		Ellipse,
		Spiral,
		RotateAroundBoss,
	};
}

class ACheckFishCharacter;

UCLASS()
class MYFISH_API AFish : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* MeshComponent;

	UPROPERTY(Category = AI, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* CheckSphere;

public:

	// Sets default values for this actor's properties
	AFish();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FishFlock)
		float SeparationWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FishFlock)
		float EnemyWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FishFlock)
		float MaxMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FishFlock)
		float BaseMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FishFlock)
		float TurnSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FishFlock)
		float CurrentMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FishFlock)
		float distBehindSpeedUpRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FishFlock)
		float FollowLeaderWeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FishFlock)
		AFishLeader *Leader;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FishFlock)
		TSubclassOf<AFishLeader> LeaderClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FishFlock|Wander")
		float WanderRangeX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FishFlock|Wander")
		float WanderRangeY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FishFlock|Wander")
		float WanderRangeZ;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FishFlock)
		FVector DestLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FishFlock|Wander")
		float MaxModifyDestInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FishFlock|Wander")
		float MinModifyDestInterval;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FishFlock)
	// 	bool EnableFollowLeaderPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FishFlock)
		TEnumAsByte<FishMoveMode::Type> MoveMode = FishMoveMode::Common;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FishFlock)
		float tempWeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FishFlock)
		FVector TempGG;




	// wander;
	void SetSpawnLocation();
	bool IsAlreadyWander;
	bool IsSetSpawnLocation;
	void SetDestLocationNSpeed();
	float ModifyDestInterval;
	FTimerHandle UnusedHandle;

	FVector SeparationComponent;
	FVector FollowLeaderComponent;
	FVector EnemyComponent;

	ACheckFishCharacter *MyPawn;
	APlayerController* PController;
	FVector2D ScreenPosition;

	float	AgentPhysicalRadius;

	float DistanceToPawn;
	FVector leaderLocation;
	TArray<AActor *> Neighbourhood;
	FVector temp_vector;
	FRotator NewRotation;
	FVector NewDirection;

	float SmallSphereRadius;
	FVector SmallSphereLocation;

	float MiddleSphereRadius;
	FVector MiddleSphereLocation;

	float LargeSphereRadius;

	float CheckEnemySmallSphereRadius;
	FVector CheckEnemySmallSphereLocation;

	float CheckEnemyMiddleSphereRadius;
	FVector CheckEnemyMiddleSphereLocation;

	bool isAtCenter;

	float ScreenMaxX;

	float ScreenMaxY;

	float ScreenMinX;

	float ScreenMinY;

	float ScreenSecondMaxX;

	float ScreenSecondMaxY;

	float ScreenSecondMinX;

	float ScreenSecondMinY;


	float ScreenCenterMaxX;

	float ScreenCenterMaxY;

	float ScreenCenterMinX;

	float ScreenCenterMinY;

	float GameViewportSizeX;
	float GameViewportSizeY;

	float CurrentSphereRadius;
	FVector CurrentFishLocation;

	FVector SpecificNeighborLocation;
	float NeighbourhoodNum;

	bool IsHasEnemy;

	void ResetComponents();

	void CalculateFlockNewMoveVector(float DeltaTime);
	void CommonAndStrictFollowLeaderPathAndWanderMode(float DeltaTime);
	void EllipseMode();
	void SpiralMode();
	void RotateAroundBossMode();

	void SetWanderMode();
	void SetLeader();
	void GetGameViewportSizeUntilGet();
	void UpdateTickIntervalAndCheckSphereRadius(bool _IsHasEnemy, FVector _CurrentFishLocation);
	// void MoveMode();

	FVector2D GetGameViewportSize();

	FVector2D GetGameResolution();
		
	FVector SpawnLocation;

	int NextIndex;
	FVector LastDestLocation;

protected:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FishFlock)
	FVector NewMoveVector;

	bool IsSetLeaderUp;
	bool IsGetGameViewportSize;
};
