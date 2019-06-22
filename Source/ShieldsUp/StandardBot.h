// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StandardBot.generated.h"

UCLASS()
class SHIELDSUP_API AStandardBot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStandardBot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void Float(float DeltaTime);
	void Rotate(float DeltaTime);

public:	
	float RunningTime;
	
	UPROPERTY(Transient, EditAnywhere, Category = "Floating Properties")
	float HeightScale;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
