// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "InvenSlotWidget.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"



UCLASS()
class UNREALFPS_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

	void GetItem(int32 ItemNum);

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

	enum class ECameraMode
	{
		EXPLORE,
		FPS
	};

	void SetCameraMode(ECameraMode NewMode);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void OnFireMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	bool IsOpenPortal();

public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Stat)
		class UFPSCharacterStatComponent* CharacterStat;

	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* StatWidget;

	UPROPERTY(VisibleAnywhere, Category = Sound)
		UAudioComponent* Attack_Sound;

	UPROPERTY()
		class AFPSPlayerController* FPSPlayerController;

	UPROPERTY()
		class AWeapon* CurWeapon;

	// ī�޶� ��ġ������ �ѱ� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset = FVector(50.0f, 30.0f, 0.0f);

	// ������ų ������Ÿ�� Ŭ����
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TArray<FItemData> Inventory;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void Turn(float Value);
	void DoCrouch();
	void ViewChange();
	void Fire();
	void UseSlot1();
	void UseSlot2();
	void Interact();
	void NoInteract();
	

private:
	ECameraMode CurMode;
	FVector DirectionToMove = FVector::ZeroVector;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;
	
	UPROPERTY()
		class UFPSAnimInstance* AnimInstance;

	bool IsInteract;
};
