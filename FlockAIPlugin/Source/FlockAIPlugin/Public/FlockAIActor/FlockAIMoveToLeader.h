// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FlockAIBase.h"
#include "FlockAIMoveToLeader.generated.h"


UCLASS()
class AFlockAIMoveToLeader : public AFlockAIBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAI|GeneralConfig")
		float distBehindSpeedUpRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAI|GeneralConfig")
		TSubclassOf<AFlockAILeader> FlockAILeaderClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAI|GeneralConfig")
		float FlySpeed;

public:
	AFlockAIMoveToLeader();

	bool SetFlockAILeader(AFlockAILeader* FlockLeader);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

	AFlockAILeader *MyFlockAILeader;

	virtual void CalcMoveToComponent() override;

	virtual void CalcMoveSpeed(const float DeltaTime) override;

	void TurnRound(float DeltaTime);

	void RandMove(float DeltaTime);

private:

	bool bIsRandom;				
	bool bIsMove;				
	bool bIsReset;				
	FVector Distance;			
	float Radius;				
	bool bIsNearFlockLeaderl;	
	float RandSpeed;			
	FVector LastLocation;		
	FVector MoveDirection;		
	float RandMoveDist;			
	FVector InitLocation;		
	float RandMoveTime;			
	float LimitTime;			
	float RandScale;			
};