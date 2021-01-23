// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALFPS_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMonsterAIController();
	virtual void OnPossess(APawn* InPawn) override;
	void RunAI();
	void StopAI();

public:
	static const FName OriginPosKey;
	static const FName SearchPosKey;
	static const FName TargetKey;

private:
	UPROPERTY()
		class UBehaviorTree* BTAsset;

	UPROPERTY()
		class UBlackboardData* BBAsset;
};
