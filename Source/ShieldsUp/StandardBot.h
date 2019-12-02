// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/Actor.h"
#include "AIController.h"
#include "StandardBot.generated.h"

UCLASS()
class SHIELDSUP_API AStandardBot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStandardBot(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	
	void Float(float DeltaTime);
	void Rotate(float DeltaTime);
	void PawnSensorSetup(const FObjectInitializer& ObjectInitializer);

public:	
	
	float RunningTime;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	class AAIController* AIController_m;
	
	UPROPERTY(Transient, EditAnywhere, Category = "Floating Properties")
	float HeightScale;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	class UPawnSensingComponent* PawnSensor;

	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UFUNCTION()
	void OnSeePawn(APawn* OtherPawn);

	UFUNCTION()
	void ManuallySetController(AAIController* controller);

	AController* GetController();
	
	//UFUNCTION()
	//void OnHearNoise(APawn *OtherActor, const FVector &Location, float Volume);
	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
