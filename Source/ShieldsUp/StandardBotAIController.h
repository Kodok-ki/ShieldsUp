// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "StandardBotAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHIELDSUP_API AStandardBotAIController : public AAIController
{
	GENERATED_BODY()
	private:
		UBehaviorTreeComponent* BehaviorTreeComp;
		UBlackboardComponent* BlackboardComp;
	
	public:
		AStandardBotAIController();

		UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName BBKeySeen = "SeenTarget";

		UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName BBKeyHeard = "HeardTarget";

		virtual void OnPossess(APawn* PossessedPawn) override;

		void SetSeenTargetInBlackboard(APawn* SeenPawn);
		void SetHeardTargetInBlackboard(APawn* HeardPawn);
};
