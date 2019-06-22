// Fill out your copyright notice in the Description page of Project Settings.


#include "StandardBot.h"

// Sets default values
AStandardBot::AStandardBot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStandardBot::BeginPlay()
{
	Super::BeginPlay();

	RunningTime = 0.f;
	HeightScale = 12.0f;
	
}

// Called every frame
void AStandardBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AStandardBot::Float(DeltaTime);

}


void AStandardBot::Float(float DeltaTime)
{
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * HeightScale;       //Scale our height by a factor of 20
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
}

void AStandardBot::Rotate(float DeltaTime)
{
	
}


