// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Monster.h"
#include "NormalMonster.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);
/**
 * 
 */
UCLASS()
class UNREALFPS_API ANormalMonster : public AMonster
{
	GENERATED_BODY()

public:
		ANormalMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnAttackEndDelegate OnAttackEnd;
	void Attack();
	void AttackCheck();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
		void ToggleUI(bool IsHiddenUI);

private:
	bool IsAttacking;

	UPROPERTY()
		class UMonsterAnimInstance* MonsterAnim;

	UPROPERTY()
		class AMonsterAIController* MonsterAIController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State, Meta = (AllowPrivateAccess = true))
		float DeadTimer;

	FTimerHandle DeadTimerHandle;

	UPROPERTY()
		USphereComponent* CollisionSphere;

	UPROPERTY()
		UAudioComponent* Dead_Sound;


};
