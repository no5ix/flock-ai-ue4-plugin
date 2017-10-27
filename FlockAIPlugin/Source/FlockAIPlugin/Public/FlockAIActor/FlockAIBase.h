// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FlockAIBase.generated.h"

class AFlockAILeader;
class AFlockAISpawner;
class AFlockAICheckCharacter;

UCLASS()
class AFlockAIBase : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleDefaultsOnly, Category = "Flock")
	USceneComponent* SceneRoot;

	UPROPERTY(Category = "FlockAI", VisibleDefaultsOnly)
	USphereComponent* CheckSphere;

	UPROPERTY(Category = "FlockAI", VisibleDefaultsOnly)
	USkeletalMeshComponent* FlockAIBody;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAI|GeneralConfig")
	float SeparationWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAI|GeneralConfig")
	float EnemyWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAI|GeneralConfig")
	float MoveToWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAI|GeneralConfig")
	float MaxMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAI|GeneralConfig")
	float BaseMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAI|GeneralConfig")
	float MeetEnemyMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAI|GeneralConfig")
	float BaseTurnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAI|GeneralConfig")
	float MeetEnemyTurnSpeed;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAI|OptimizeConfig")
		float TickIntervalBias;

protected:
	// static const var
	static const UClass *AFlockAIBaseUClass;
	static const UClass *AFlockAIEnemyUClass;
	static const ECollisionChannel CollisionChannel;


	// temp
	FVector CurrentFlockAILocation;
	float CurrentMovementSpeed;
	FVector SpecificNeighbourLocation;
	TSet<AActor*> Neighbourhood;

	// New move vector component
	FVector SeparationComponent;
	FVector MoveToComponent;
	FVector EnemyComponent;

	// flag
	bool bIsHasEnemy;

	// Update tick interval
	FVector VectorCharCameraToFlockAI;
	float VectorSizeCharCameraToFlockAI;
	float TempDotProduct;

	bool bIsTooFar;

	void ResetComponents();

protected:

	AFlockAISpawner *MyFlockAISpawner;

	APlayerCameraManager *CurrentPlayerCameraMgr;

	uint32 FlockAISerialNumber;

public:

	void SetFlockAICheckCharCameraComp();

	void SetFlockAISpawner(AFlockAISpawner *spawner);

	void SetFlockAISerialNumber(const float sn);

public:
	// Sets default values for this actor's properties
	AFlockAIBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	virtual void ProcessMoveEvent(const float DeltaTime);

	virtual void CalcMoveToComponent() PURE_VIRTUAL(AFlockAIBase::CalcMoveToComponent(), );

	virtual void CalcMoveSpeed(const float DeltaTime) PURE_VIRTUAL(AFlockAIBase::CalcMoveSpeed(), );

	virtual void UpdateTickInterval();
	
};
