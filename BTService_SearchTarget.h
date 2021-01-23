// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_SearchTarget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALFPS_API UBTService_SearchTarget : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_SearchTarget();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
