#include "FlockAIPlugin.h"
#include "FlockAIMoveToLeader.h"



AFlockAIMoveToLeader::AFlockAIMoveToLeader()
{
	PrimaryActorTick.bCanEverTick = true;

	MyFlockAILeader = nullptr;
	distBehindSpeedUpRange = 800.f;
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

bool AFlockAIMoveToLeader::SetFlockAILeader()
{
	if (MyFlockAILeader == nullptr)
	{
		TArray<AActor*> FlockAILeaderArray;
		UGameplayStatics::GetAllActorsOfClass(this, FlockAILeaderClass, FlockAILeaderArray);
		if (FlockAILeaderArray.Num())
		{
			MyFlockAILeader = Cast<AFlockAILeader>(FlockAILeaderArray[0]);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}

void AFlockAIMoveToLeader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SetFlockAILeader())
	{
		UpdateTickInterval();
		ProcessMoveEvent(DeltaTime);
	}
}
