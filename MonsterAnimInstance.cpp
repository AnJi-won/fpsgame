// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "Monster.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
	Speed = 0.0f;
	IsInAir = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> MT_Attack(
		TEXT("/Game/Animation/AnimMT_MonsterAttack.AnimMT_MonsterAttack"));
	if (MT_Attack.Succeeded())
	{
		AttackMontage = MT_Attack.Object;
	}
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMonster* Pawn = Cast<AMonster>(TryGetPawnOwner());
	if (!::IsValid(Pawn)) return;
	if (!IsDead)
	{
		Speed = Pawn->GetCharacterMovement()->Velocity.Size();
		IsInAir = Pawn->GetMovementComponent()->IsFalling();
	}
}

void UMonsterAnimInstance::PlayAttackMontage()
{
	if(!IsDead)
		Montage_Play(AttackMontage, 1.0f);
}

void UMonsterAnimInstance::AnimNotify_HitCheck()
{
	OnHitCheck.Broadcast();
}
