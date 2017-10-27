#include "FlockAIPlugin.h"
#include "FlockAIMoveToLeader.h"
#include "FlockAILeader.h"
#include "Kismet/KismetMathLibrary.h"


AFlockAIMoveToLeader::AFlockAIMoveToLeader()
{
	PrimaryActorTick.bCanEverTick = true;

	MyFlockAILeader = nullptr;
	distBehindSpeedUpRange = 300.0f;
	bIsRandom = false;
	bIsMove = false;
	bIsReset = true;
	RandMoveDist = 200.0f;
	FlySpeed = 25.f;
}

void AFlockAIMoveToLeader::CalcMoveToComponent()
{
	// calc MoveToComponent
	MoveToComponent = (MyFlockAILeader->GetActorLocation() - CurrentFlockAILocation);
	MoveToComponent.GetSafeNormal();
}

void AFlockAIMoveToLeader::CalcMoveSpeed(const float DeltaTime)
{
	if (GetDistanceTo(MyFlockAILeader) > distBehindSpeedUpRange)
	{
		CurrentMovementSpeed = CurrentMovementSpeed + DeltaTime * (MaxMovementSpeed - CurrentMovementSpeed);
	}
	else
	{
		CurrentMovementSpeed = CurrentMovementSpeed + DeltaTime * (BaseMovementSpeed - CurrentMovementSpeed);
	}

}

void AFlockAIMoveToLeader::TurnRound(float DeltaTime)
{
	CheckSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CheckSphere->SetComponentTickEnabled(false);
	FlockAIBody->SetComponentTickEnabled(false);

	bIsNearFlockLeaderl = (GetActorLocation() == InitLocation);

	if (!bIsNearFlockLeaderl)
	{
		ResetComponents();
		CalcMoveToComponent();
		CalcMoveSpeed(DeltaTime);
		SetActorRotation(FMath::RInterpTo(GetActorRotation(),
			UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), InitLocation),
			DeltaTime,
			BaseTurnSpeed));
		AddActorWorldOffset(GetActorForwardVector() * DeltaTime * CurrentMovementSpeed);
	}

	if (bIsReset && bIsNearFlockLeaderl)
	{
		Distance = GetActorLocation() - MyFlockAILeader->GetActorLocation();
		bIsRandom = FMath::RandBool();
		Radius = FMath::Sqrt(Distance.X * Distance.Y + Distance.Y * Distance.Y);
		RandSpeed = FMath::FRandRange(0.5f, 1.5f);
		LastLocation = FVector(0.0f, 0.0f, 0.0f);
	}

	if (GetWorld() && bIsNearFlockLeaderl)
	{
		if (bIsRandom)
		{
			float TempX = FMath::Sin(PI / (180.f) * (GetWorld()->GetTimeSeconds() * FlySpeed * RandSpeed)) * Radius;
			float TempY = FMath::Cos(PI / (180.f) * (GetWorld()->GetTimeSeconds() * FlySpeed * RandSpeed)) * Radius;
			SetActorLocation(MyFlockAILeader->GetActorLocation() + FVector(TempX, TempY, InitLocation.Z));		
			FRotator ActorRotator = UKismetMathLibrary::ComposeRotators(UKismetMathLibrary::MakeRotFromX(GetActorLocation() - LastLocation), FRotator(0.0f, 0.0f, 0.0f));
			LastLocation = GetActorLocation();
			SetActorRotation(ActorRotator);
		}
		else
		{
			float TempX = FMath::Sin(PI / (180.f) * (GetWorld()->GetTimeSeconds() * FlySpeed * (-1) * RandSpeed)) * Radius;
			float TempY = FMath::Cos(PI / (180.f) * (GetWorld()->GetTimeSeconds() * FlySpeed * (-1) * RandSpeed)) * Radius;
			SetActorLocation(MyFlockAILeader->GetActorLocation() + FVector(TempX, TempY, InitLocation.Z));
			FRotator ActorRotator = UKismetMathLibrary::ComposeRotators(UKismetMathLibrary::MakeRotFromX(GetActorLocation() - LastLocation), FRotator(0.0f, 0.0f, 0.0f));
			LastLocation = GetActorLocation();
			SetActorRotation(ActorRotator);
		}

	}
}

void AFlockAIMoveToLeader::RandMove(float DeltaTime)
{
	CheckSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CheckSphere->SetComponentTickEnabled(false);
	FlockAIBody->SetComponentTickEnabled(false);
	if (!bIsReset)
	{
		ResetComponents();
		CalcMoveToComponent();
		CalcMoveSpeed(DeltaTime);
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), MyFlockAILeader->GetActorLocation()));
		RandMoveTime += DeltaTime;

		if (RandMoveTime <= LimitTime)
		{
			bIsReset = false;
			float TempValue = FMath::Cos(PI / (180.f) * (GetWorld()->GetTimeSeconds() * RandScale));
			FVector TempLoc = (GetActorForwardVector() * DeltaTime * CurrentMovementSpeed) + (RandMoveDist * MoveDirection * TempValue * DeltaTime);
			AddActorWorldOffset(TempLoc);
		}
		else
		{
			RandMoveTime = 0.0f;
			bIsReset = true;
		}
	}
}

bool AFlockAIMoveToLeader::SetFlockAILeader(AFlockAILeader* FlockLeader)
{
	if (MyFlockAILeader == nullptr)
	{
		MyFlockAILeader = FlockLeader;
		if (MyFlockAILeader)
			return true;
		else
			return false;
	}
	return true;
}

void AFlockAIMoveToLeader::BeginPlay()
{
	Super::BeginPlay();
	distBehindSpeedUpRange = FMath::FRandRange(500.0f, 1700.0f);
	InitLocation = GetActorLocation();
}

void AFlockAIMoveToLeader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SetFlockAILeader(MyFlockAILeader))
	{
		UpdateTickInterval();
		if (bIsTooFar)
		{
			if (MyFlockAILeader->bIsMove)
			{
				if (bIsReset)
				{
					MoveDirection = FMath::VRand();
					RandMoveDist = FMath::FRandRange(-200, 200);
					LimitTime = FMath::FRandRange(3.0f, 6.0f);
					RandScale = FMath::FRandRange(20.0f, 50.0f);
					bIsReset = false;
				}
				RandMove(DeltaTime);
			}
			else
			{
				TurnRound(DeltaTime);
				if (bIsReset && bIsNearFlockLeaderl)
					bIsReset = false;
			}

		}
		else
		{
			bIsReset = true;
			RandMoveTime = 0.0f;
			ProcessMoveEvent(DeltaTime);
		}
	}
}
