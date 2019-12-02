// Fill out your copyright notice in the Description page of Project Settings.


#include "StandardBotAIController.h"
#include "StandardBotPawn.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

AStandardBotAIController::AStandardBotAIController()
{
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

void AStandardBotAIController::OnPossess(APawn* PossessedPawn)
{
	Super::OnPossess(PossessedPawn);

	AStandardBotPawn* StandardBot = Cast<AStandardBotPawn>(PossessedPawn);
	if (StandardBot)
	{
		if (StandardBot->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(StandardBot->BehaviorTree->BlackboardAsset));
			BehaviorTreeComp->StartTree(*StandardBot->BehaviorTree);
		}
	}
}

void AStandardBotAIController::SetSeenTargetInBlackboard(APawn* SeenPawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(BBKeySeen, SeenPawn);
	}
}

void AStandardBotAIController::SetHeardTargetInBlackboard(APawn* HeardPawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(BBKeyHeard, HeardPawn);
	}
}
