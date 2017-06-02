// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Info.h"
//#include "FlockAIBase.h"
#include "FlockAISpawner.generated.h"

class AFlockAIBase;

/**
 * 
 */
UCLASS()
class AFlockAISpawner : public AActor
{
	GENERATED_BODY()
	
public:

	AFlockAISpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAISpawner")
		TSubclassOf<AFlockAIBase> FlockAIType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAISpawner")
		int FlockAIAmount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAISpawner")
		float FlockAILifeSpan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAISpawner")
		float SpawnDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAISpawner")
		float SpawnMaxRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAISpawner")
		float SpawnMinRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAISpawner")
		int TickFlockAIAmountPerFrame;

public:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "FlockAISpawner")
		void SpawnFlockAI();

	virtual void Tick(float DeltaSeconds) override;
	
	bool CanProcessTick(uint32 FlockAISerialNum) const;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAISpawner")
	//	int CanTickSerialNumber;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAISpawner")
	//	int MaxCanTickSerialNumber;

	uint32 CanTickSerialNumber;

	uint32 MaxCanTickSerialNumber;

private:
	//uint32 CanTickSerialNumber;

	//uint32 MaxCanTickSerialNumber;

	float SpawnRangeMaxX;
	float SpawnRangeMaxY;
	float SpawnRangeMaxZ;

	float SpawnRangeMinX;
	float SpawnRangeMinY;
	float SpawnRangeMinZ;

	FTransform SpawnTrans;

	uint32 CurrentFlockAICount;

	FTimerHandle SpawnFlockAITimeHandle;

	void LoopSpawn();

	void DoSpawnFlockAI();

};
