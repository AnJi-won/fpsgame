// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AMonsterAIController::OriginPosKey(TEXT("OriginPos"));
const FName AMonsterAIController::SearchPosKey(TEXT("SearchPos"));
const FName AMonsterAIController::TargetKey(TEXT("Target"));

AMonsterAIController::AMonsterAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(
		TEXT("/Game/AI/BB_MonsterAI.BB_MonsterAI"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(
		TEXT("/Game/AI/BT_MonsterAI.BT_MonsterAI"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	/*if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(OriginPosKey, InPawn->GetActorLocation());

		if (!RunBehaviorTree(BTAsset))
		{
			
		}
	}*/
}

void AMonsterAIController::RunAI()
{
	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(OriginPosKey, GetPawn()->GetActorLocation());

		if (!RunBehaviorTree(BTAsset))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AIController couldn't run behavior tree!"));
		}
	}
}

void AMonsterAIController::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr != BehaviorTreeComponent)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}
