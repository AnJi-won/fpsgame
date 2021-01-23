// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnHitCheckDelegate);

/**
 * 
 */
UCLASS()
class UNREALFPS_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMonsterAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	void PlayAttackMontage();
	void SetDeadAnim() { IsDead = true; }


public:
	FOnHitCheckDelegate OnHitCheck;

private:
	UFUNCTION()
		void AnimNotify_HitCheck();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsDead;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage;
};
