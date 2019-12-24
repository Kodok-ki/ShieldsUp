// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TimerManager.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "StandardBotPawn.generated.h"

UCLASS()
class SHIELDSUP_API AStandardBotPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AStandardBotPawn(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	//void Float(float DeltaTime);
	//void Rotate(float DeltaTime);
	void PawnSensorSetup(const FObjectInitializer& ObjectInitializer);
	

public:	

	UPROPERTY()
	UWorld* SBotWorld;
	
	UPROPERTY()
	FVector SBotLocation;
	
	UPROPERTY()
	FRotator SBotRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EnemyStats")
	int HealthPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EnemyStats")
	bool bIsAlive;
	
	UPROPERTY()
	FTimerHandle TimerHandler;
	//float RunningTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float RInterpSpeed;


	UPROPERTY(Transient, EditAnywhere, Category = "Floating Properties")
	float HeightScale;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	class UPawnSensingComponent* PawnSensor;

	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AActor> Projectile;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Shoot();

	UFUNCTION()
	void OnSeePawn(APawn* OtherPawn);

	UFUNCTION()
	void OnHearNoise(APawn* InstigatorPawn, const FVector& Location, float Volume);

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void TakeDamage(const float Damage);

	//Rotation in yaw axis only
	UFUNCTION(BlueprintCallable, Category = "AI")
	void RotateYawTowardsOtherActor(const AActor* OtherActor);

};
