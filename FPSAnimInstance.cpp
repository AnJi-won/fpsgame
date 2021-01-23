// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAnimInstance.h"
#include "FPSCharacter.h"

UFPSAnimInstance::UFPSAnimInstance()
{
	Speed = 0.0f;
	Crouching = false;
	EnableJump = false;
	IsDead = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> MT_FIRE(
		TEXT("/Game/Animation/AnimMT_FPSAttack.AnimMT_FPSAttack"));
	if (MT_FIRE.Succeeded())
	{
		FireMontage = MT_FIRE.Object;
	}
}

void UFPSAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AFPSCharacter* Pawn = Cast<AFPSCharacter>(TryGetPawnOwner());
	if (!::IsValid(Pawn)) return;

	if (!IsDead)
	{
		Speed = Pawn->GetCharacterMovement()->Velocity.Size();
		Direction = CalculateDirection(Pawn->GetCharacterMovement()->Velocity, Pawn->GetActorRotation());
		Crouching = Pawn->GetCharacterMovement()->bWantsToCrouch;
		EnableJump = Pawn->GetMovementComponent()->IsFalling();
	}
}

void UFPSAnimInstance::PlayFireMontage()
{
	if (!IsDead)
	{
		Montage_Play(FireMontage, 1.0f);
	}
}
