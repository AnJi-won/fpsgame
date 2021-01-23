// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SearchPos.h"
#include "MonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_SearchPos::UBTTask_SearchPos()
{
	NodeName = TEXT("SearchPos");
}

EBTNodeResult::Type UBTTask_SearchPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if(nullptr == NavSystem)
		return EBTNodeResult::Failed;

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AMonsterAIController::OriginPosKey);
	FNavLocation NextPos;

	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextPos))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AMonsterAIController::SearchPosKey, NextPos.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
