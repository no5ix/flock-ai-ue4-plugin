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

#include "MyFish.h"
#include "CheckFishCharacter.h"


// Sets default values
ACheckFishCharacter::ACheckFishCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SumNearbyFish = 0.0f;

	float SphereRadius = 300.0f;



	SceneCpp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneCpp"));
	SceneCpp->AttachTo(RootComponent);
	SceneCpp->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));

	CameraCpp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraCpp"));
	CameraCpp->AttachTo(SceneCpp);

	CheckSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CheckSphere"));
	CheckSphere->AttachTo(CameraCpp);
	CheckSphere->SetSphereRadius(SphereRadius);
	CheckSphere->SetRelativeLocation(FVector(SphereRadius, 0.0f, 0.0f));

	CheckSphere->OnComponentBeginOverlap.AddDynamic(this, &ACheckFishCharacter::OnBeginOverlap);
	CheckSphere->OnComponentEndOverlap.AddDynamic(this, &ACheckFishCharacter::OnEndOverlap);
}

void ACheckFishCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	if (NeighborhoodTypes.Find(OtherActor->GetClass()) >= 0)
	{
		SumNearbyFish++;
	}

}

void ACheckFishCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (NeighborhoodTypes.Find(OtherActor->GetClass()) >= 0)
	{
		SumNearbyFish--;
	}
}