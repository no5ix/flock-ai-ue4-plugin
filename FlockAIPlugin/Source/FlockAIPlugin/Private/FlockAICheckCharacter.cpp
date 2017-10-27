// Fill out your copyright notice in the Description page of Project Settings.

#include "FlockAIPlugin.h"
#include "FlockAICheckCharacter.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"


// Sets default values
AFlockAICheckCharacter::AFlockAICheckCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	MoveSpeed = 20.f;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FlockAICharCamera"));
	CameraComp->SetupAttachment(RootComponent);
	CameraComp->bUsePawnControlRotation = true;

	//LeftHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("FlockAILeftHand"));
	//LeftHand->Hand = EControllerHand::Left;
	//LeftHand->SetupAttachment(RootComponent);

	//RightHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("FlockAIRightHand"));
	//RightHand->Hand = EControllerHand::Right;
	//RightHand->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFlockAICheckCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayConnected())
	{
		UHeadMountedDisplayFunctionLibrary::EnableHMD(true);
	}
}

// Called every frame
//void AFlockAICheckCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

// Called to bind functionality to input
void AFlockAICheckCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis("MoveUp", this, &AFlockAICheckCharacter::MoveUp);
	PlayerInputComponent->BindAxis("MoveForward", this, &AFlockAICheckCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFlockAICheckCharacter::MoveRight);

	PlayerInputComponent->BindAxis("SpeedUp", this, &AFlockAICheckCharacter::SpeedUp);
	PlayerInputComponent->BindAxis("SpeedDown", this, &AFlockAICheckCharacter::SpeedDown);

}

void AFlockAICheckCharacter::MoveForward(float Val)
{
	if (Controller && Val != 0.f)
	{
		AddActorWorldOffset(CameraComp->GetForwardVector() * Val * MoveSpeed);
		//AddMovementInput(FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X), Val * MoveSpeed);
	}
}

void AFlockAICheckCharacter::MoveRight(float Val)
{
	if (Val != 0.f)
	{
		AddActorWorldOffset(CameraComp->GetRightVector() * Val * MoveSpeed);
		//AddMovementInput(FQuatRotationMatrix(GetActorQuat()).GetScaledAxis(EAxis::Y), Val * MoveSpeed);
	}

}

void AFlockAICheckCharacter::MoveUp(float Val)
{
	if (Val != 0.f)
	{
		AddActorWorldOffset(FVector::UpVector * Val * MoveSpeed);
		//AddMovementInput(FVector::UpVector, Val * MoveSpeed);
	}
}

void AFlockAICheckCharacter::SpeedUp(float Val)
{
	if (Val != 0.f)
	{
		MoveSpeed += Val;
	}
}

void AFlockAICheckCharacter::SpeedDown(float Val)
{
	if (Val != 0.f)
	{
		MoveSpeed -= Val;
	}
}
