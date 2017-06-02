// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FlockAIBase.h"
#include "FlockAIWander.generated.h"


UCLASS()
class AFlockAIWander : public AFlockAIBase
{
	GENERATED_BODY()

public:
	AFlockAIWander();
protected:

	virtual void CalcMoveToComponent() override;

	virtual void CalcMoveSpeed(const float DeltaTime) override;

};