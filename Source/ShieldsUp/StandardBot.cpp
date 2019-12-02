// Fill out your copyright notice in the Description page of Project Settings.


#include "StandardBot.h"
#include "StandardBotAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIController.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AStandardBot::AStandardBot(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSensorSetup(ObjectInitializer);
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

void AStandardBot::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensor->OnSeePawn.AddDynamic(this, &AStandardBot::OnSeePawn);
	//UE_LOG(LogTemp, Warning, TEXT("OnSeePawn.AddDynamic called."));
}


void AStandardBot::Float(float DeltaTime)
{
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * HeightScale;       //Scale our height by a factor of 20
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
}

void AStandardBot::PawnSensorSetup(const FObjectInitializer& ObjectInitializer)
{
	PawnSensor = ObjectInitializer.CreateDefaultSubobject<UPawnSensingComponent>(this, TEXT("Pawn Sensor"));
	PawnSensor->bOnlySensePlayers = true;
	PawnSensor->SensingInterval = 0.25f;
	PawnSensor->SetPeripheralVisionAngle(90.f);
}

void AStandardBot::ManuallySetController(AAIController* controller)
{
	AStandardBot::AIController_m = controller;
}

AController* AStandardBot::GetController()
{
	return AIController_m;
}

void AStandardBot::OnSeePawn(APawn* OtherPawn)
{
	AStandardBotAIController* AIController = Cast<AStandardBotAIController>(OtherPawn->GetController());
	UE_LOG(LogTemp, Warning, TEXT("AIController cast attempted."));
	if (AIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnSeePawn called."));
		AIController->SetSeenTargetInBlackboard(OtherPawn);
	}
	//FString message = TEXT("StandardBot has seen: ") + OtherPawn->GetName();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);
	//UE_LOG(LogTemp, Warning, TEXT("StandardBot has seen: "));
	//TODO: Add the rest of StandardBot's behavior
}

