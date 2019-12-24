// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "vector"
#include "EnemySpawner.generated.h"

class UWorld;

UCLASS()
class SHIELDSUP_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	FTimerHandle TimerHandle;

	UFUNCTION()
	void SpawnHandler();

	UFUNCTION()
	void GenerateSpawnPoints();

public:	

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> EnemyType;

	std::vector<FVector> SpawnPoints;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
