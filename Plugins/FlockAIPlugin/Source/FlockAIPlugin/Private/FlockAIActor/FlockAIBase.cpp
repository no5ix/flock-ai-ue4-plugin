// Fill out your copyright notice in theDescription page of Project Settings.

#include "FlockAIPlugin.h"
#include "FlockAIBase.h"
#include "FlockAISpawner.h"
#include "FlockAIEnemy.h"
#include "FlockAICheckCharacter.h"
#include "FlockAILeader.h"

const UClass* AFlockAIBase::AFlockAIBaseUClass = AFlockAIBase::StaticClass();
const UClass* AFlockAIBase::AFlockAIEnemyUClass = AFlockAIEnemy::StaticClass();
const ECollisionChannel AFlockAIBase::CollisionChannel = ECC_GameTraceChannel2;


// Sets default values
AFlockAIBase::AFlockAIBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FlockAISerialNumber = 0;

	MyFlockAISpawner = nullptr;

	// OptimizeConfig
	TickIntervalBias = 0.12f;

	// Update tick interval
	VectorCharCameraToFlockAI = FVector(0.f, 0.f, 0.f);
	VectorSizeCharCameraToFlockAI = 0.f;
	TempDotProduct = 0.f;

	// GeneralConfig
	SeparationWeight = 200.f;
	EnemyWeight = 1400.f;
	MaxMovementSpeed = 600.f;
	BaseMovementSpeed = 150.f;
	MeetEnemyMovementSpeed = 300.f;
	BaseTurnSpeed = 1.f;
	MeetEnemyTurnSpeed = 10.f;
	MoveToWeight = 5.f;


	// temp
	CurrentMovementSpeed = 0.f;
	CurrentFlockAILocation = FVector(0.f, 0.f, 0.f);
	SpecificNeighbourLocation = FVector(0.f, 0.f, 0.f);

	// New move vector component
	SeparationComponent = FVector(0, 0, 0);
	EnemyComponent = FVector(0, 0, 0);
	MoveToComponent = FVector(0, 0, 0);

	// flag
	bIsHasEnemy = false;

	// 
	CheckSphere = CreateDefaultSubobject<USphereComponent>(TEXT("FlockAICheckSphere"));
	CheckSphere->SetSphereRadius(10.f);

	RootComponent = CheckSphere;

	FlockAIBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FlockAIBody"));
	FlockAIBody->SetupAttachment(CheckSphere);
	FlockAIBody->CastShadow = false;
	FlockAIBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AFlockAIBase::BeginPlay()
{
	Super::BeginPlay();
	
	SetFlockAICheckCharCameraComp();
}

void AFlockAIBase::ProcessMoveEvent(const float DeltaTime)
{
	{
		//if (MyFlockAISpawner->CanProcessTick(FlockAISerialNumber))
		{
			ResetComponents();

			// calc separation component & enemy component
			CheckSphere->GetOverlappingActors(Neighbourhood);
			for (auto &TempNeighbour : Neighbourhood)
			{
				SpecificNeighbourLocation = TempNeighbour->GetActorLocation();
				if (TempNeighbour->GetClass()->IsChildOf(AFlockAIEnemyUClass))
				{
					ResetComponents();
					EnemyComponent = CurrentFlockAILocation - SpecificNeighbourLocation;
					bIsHasEnemy = true;
					break;
				}
				if (TempNeighbour->GetClass()->IsChildOf(AFlockAIBaseUClass))
				{
					if (TempNeighbour != this)
					{
						SeparationComponent += CurrentFlockAILocation - SpecificNeighbourLocation;
					}
				}
			}


			if (!bIsHasEnemy)
			{
				CalcMoveToComponent();

				CalcMoveSpeed(DeltaTime);
			}
			else
			{
				//CurrentMovementSpeed = FMath::Lerp(CurrentMovementSpeed, MeetEnemyMovementSpeed, DeltaTime);
				CurrentMovementSpeed = MeetEnemyMovementSpeed;
			}

			// calc rotation
			SetActorRotation(
				FMath::RInterpTo(
					GetActorRotation(),
					(SeparationComponent * SeparationWeight +
						EnemyComponent * EnemyWeight +
						MoveToComponent * MoveToWeight).ToOrientationRotator(),
					DeltaTime,
					(bIsHasEnemy ? MeetEnemyTurnSpeed : BaseTurnSpeed)
				)
			);
		}

		AddActorWorldOffset(GetActorForwardVector() * DeltaTime * CurrentMovementSpeed);
	}
}

void AFlockAIBase::UpdateTickInterval()
{
	VectorCharCameraToFlockAI = CurrentFlockAILocation - CurrentPlayerCameraMgr->GetCameraLocation();

	VectorSizeCharCameraToFlockAI = VectorCharCameraToFlockAI.Size();

	TempDotProduct = VectorCharCameraToFlockAI.GetSafeNormal() | FQuatRotationMatrix(CurrentPlayerCameraMgr->GetActorQuat()).GetUnitAxis(EAxis::X);

	if ( VectorSizeCharCameraToFlockAI > 2000.f )
	{
		if (TempDotProduct >= 0.6f)
		{
			PrimaryActorTick.TickInterval = 0.12f - FMath::Lerp(0.1f, 0.f, VectorSizeCharCameraToFlockAI / 8000.f);
		}
		else
		{
			PrimaryActorTick.TickInterval = 0.12f;
		}
	}
	else 
	{
		if (TempDotProduct >= 0.6f)
		{
			PrimaryActorTick.TickInterval = 0.005f * FMath::Lerp(1.f, 3.f, VectorSizeCharCameraToFlockAI / 2000.f);
		}
		else
		{
			PrimaryActorTick.TickInterval = VectorSizeCharCameraToFlockAI < 500 ? 0.005f : 0.1f;
		}
	}
}

void AFlockAIBase::ResetComponents()
{
	CurrentFlockAILocation = GetActorLocation();
	SeparationComponent = FVector(0, 0, 0);
	EnemyComponent = FVector(0, 0, 0);
	MoveToComponent = FVector(0, 0, 0);
	bIsHasEnemy = false;
}


void AFlockAIBase::SetFlockAICheckCharCameraComp()
{
	CurrentPlayerCameraMgr = UGameplayStatics::GetPlayerCameraManager(this, 0);
}

void AFlockAIBase::SetFlockAISpawner(AFlockAISpawner *spawner)
{
	MyFlockAISpawner = spawner;
}

void AFlockAIBase::SetFlockAISerialNumber(const float sn)
{
	FlockAISerialNumber = sn;
}

