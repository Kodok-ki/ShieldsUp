// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "TimerManager.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GenerateSpawnPoints();

	UWorld* World = GetWorld();
	if(!TimerHandle.IsValid())
	World->GetTimerManager().SetTimer(TimerHandle, this, &AEnemySpawner::SpawnHandler, 4.5f, true);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnHandler()
{
	int EPos = FMath::FRandRange(0, 3);
	FVector EnemyLocation;
	if (!SpawnPoints.empty())
	{
		EnemyLocation = SpawnPoints.at(EPos);
	}
	else
	{
		EnemyLocation = FVector(600.f, 1000.f, 230.f);
	}
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	GetWorld()->SpawnActor(EnemyType, &EnemyLocation, new FRotator(0.f, 180.0f, 0.f), SpawnParam);
}

void AEnemySpawner::GenerateSpawnPoints()
{
	SpawnPoints.push_back(FVector(600.f, 1000.f, 230.f));
	SpawnPoints.push_back(FVector(-1500.f, -1000.f, 230.f));
	SpawnPoints.push_back(FVector(-200.f, -1200.f, 230.f));
}