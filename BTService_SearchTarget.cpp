// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SearchTarget.h"
#include "MonsterAIController.h"
#include "Monster.h"
#include "FPSCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_SearchTarget::UBTService_SearchTarget()
{
	NodeName = TEXT("SearchTarget");
	Interval = 1.0f;
}

void UBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float SearchRadius = 1000.0f;
	if (nullptr == World) return;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(SearchRadius),
		CollisionQueryParam
	);

	if (bResult)
	{
		for (auto OverlapResult : OverlapResults)
		{
			AFPSCharacter* Player = Cast<AFPSCharacter>(OverlapResult.GetActor());
			if (nullptr != Player)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMonsterAIController::TargetKey, Player);
			}
		}
	}
	//DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Green, false, 0.2f);
}
