// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SearchPos.generated.h"

/**
 * 
 */
UCLASS()
class UNREALFPS_API UBTTask_SearchPos : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_SearchPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
