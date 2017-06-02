// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "FlockAICheckCharacter.generated.h"

//class UMotionControllerComponent;

UCLASS()
class AFlockAICheckCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFlockAICheckCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UCameraComponent* GetCameraComponent() const { return CameraComp; }
	
protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "FlockAICheckChar")
		UCameraComponent *CameraComp;

	//UPROPERTY(VisibleDefaultsOnly, Category = "FlockAICheckChar")
	//	UMotionControllerComponent *LeftHand;
	//UPROPERTY(VisibleDefaultsOnly, Category = "FlockAICheckChar")
	//	UMotionControllerComponent *RightHand;

public:
	// input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlockAICheckChar|Config")
		float MoveSpeed;

	void MoveForward(float Val);
	void MoveRight(float Val);
	void MoveUp(float Val);

	void SpeedUp(float Val);
	void SpeedDown(float Val);
};
