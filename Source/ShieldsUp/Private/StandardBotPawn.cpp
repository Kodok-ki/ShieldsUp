// Fill out your copyright notice in the Description page of Project Settings.


#include "StandardBotPawn.h"
#include "StandardBotAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIController.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AStandardBotPawn::AStandardBotPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSensorSetup(ObjectInitializer);
}

// Called when the game starts or when spawned
void AStandardBotPawn::BeginPlay()
{
	Super::BeginPlay();

	SpawnDefaultController();
	SBotWorld = GetWorld();
	SBotWorld->GetTimerManager().SetTimer(TimerHandler, this, &AStandardBotPawn::Shoot, 1.0f, true);
	if (PawnSensor)
	{
		PawnSensor->OnSeePawn.AddDynamic(this, &AStandardBotPawn::OnSeePawn);
		PawnSensor->OnHearNoise.AddDynamic(this, &AStandardBotPawn::OnHearNoise);
	}

	bIsAlive = true;
	HealthPoints = 3;
}

// Called every frame
void AStandardBotPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStandardBotPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AStandardBotPawn::PawnSensorSetup(const FObjectInitializer& ObjectInitializer)
{
	PawnSensor = ObjectInitializer.CreateDefaultSubobject<UPawnSensingComponent>(this, TEXT("PawnSensor"));
	PawnSensor->bOnlySensePlayers = true;
	PawnSensor->SensingInterval = 0.25f;
	PawnSensor->SetPeripheralVisionAngle(90.f);
}


void AStandardBotPawn::OnSeePawn(APawn* OtherPawn)
{
	AStandardBotAIController* AIController = Cast<AStandardBotAIController>(GetController());
	if (AIController && OtherPawn->ActorHasTag("Player"))
	{
		AIController->SetSeenTargetInBlackboard(OtherPawn);
	}
	//TODO: Add the rest of StandardBot's behavior
}

void AStandardBotPawn::OnHearNoise(APawn* InstigatorPawn, const FVector& Location, float Volume)
{
	AStandardBotAIController* AIController = Cast<AStandardBotAIController>(GetController());

	if (AIController != NULL && InstigatorPawn != this)
	{
		AIController->SetHeardTargetInBlackboard(InstigatorPawn);
	}
}

void AStandardBotPawn::Shoot()
{
	FVector ForwardVec = GetActorForwardVector();
	FVector LocationOffset = FVector(ForwardVec.X * 100, ForwardVec.Y * 100, 50.0f);
	SBotLocation = GetActorLocation() + LocationOffset;
	SBotRotation = GetActorRotation();
	SBotWorld->SpawnActor(Projectile, &SBotLocation, &SBotRotation);
}

void AStandardBotPawn::TakeDamage(float Damage)
{
	if (Damage > 0.f && bIsAlive)
	{
		HealthPoints -= Damage;
		//PrintToScreen(DamageCauser->GetName());
		if (HealthPoints <= 0.f)
		{
			bIsAlive = false;
			AActor::Destroy();
		}
	}
}

void AStandardBotPawn::RotateYawTowardsOtherActor(const AActor* OtherActor)
{
	RInterpSpeed = 5000.0f;
	SBotWorld = GetWorld();
	SBotLocation = GetActorLocation();
	SBotRotation = GetActorRotation();
	FVector OtherActorLocation = OtherActor->GetActorLocation();
	FRotator RotationDiff = UKismetMathLibrary::FindLookAtRotation(SBotLocation, OtherActorLocation);
	FRotator FinalRotation = FRotator(GetActorRotation().Pitch, RotationDiff.Yaw, GetActorRotation().Roll);
	FRotator RInterp = UKismetMathLibrary::RInterpTo_Constant(SBotRotation, FinalRotation, SBotWorld->DeltaTimeSeconds, RInterpSpeed);
	SetActorRotation(RInterp);
}