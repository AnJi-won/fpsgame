// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "FPSPlayerController.h"
#include "FPSCharacterStatComponent.h"
#include "FPSHUDWidget.h"
#include "FPSNormalGun.h"
#include "Projectile.h"
#include "FPSAnimInstance.h"
#include "PickupItem.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CharacterStat = CreateDefaultSubobject< UFPSCharacterStatComponent>(TEXT("CharacterStat"));
	Attack_Sound = CreateDefaultSubobject<UAudioComponent>(TEXT("AttackSound"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->JumpZVelocity = 300.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> FPS_MESH(
		TEXT("/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin"));
	if (FPS_MESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(FPS_MESH.Object);
	}
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> FPS_ANIM(
		TEXT("/Game/Animation/AnimBP_FPSCharacter.AnimBP_FPSCharacter_C"));
	if (FPS_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(FPS_ANIM.Class);
	}

	static ConstructorHelpers::FObjectFinder<USoundWave> SOUND_ATTACK(
		TEXT("/Game/Sound/GunShot.GunShot"));
	if (SOUND_ATTACK.Succeeded())
	{
		Attack_Sound->SetSound(SOUND_ATTACK.Object);
		Attack_Sound->bAutoActivate = false;
		Attack_Sound->SetVolumeMultiplier(3.0f);
	}
	
	SetCameraMode(ECameraMode::FPS);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	IsInteract = false;
}



void AFPSCharacter::GetItem(int32 ItemNum)
{
	switch (ItemNum)
	{
	case 1:
		FPSPlayerController->GetHUDWidget()->Slot1_AddCount();
		break;
	case 2:
		FPSPlayerController->GetHUDWidget()->Slot2_AddCount();
		break;
	}
	
	
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	FPSPlayerController = Cast<AFPSPlayerController>(GetController());
	if (nullptr != FPSPlayerController)
	{
		CharacterStat->SetCharacterStat(100.0f, 50.0f);
		FPSPlayerController->GetHUDWidget()->BindCharacterStat(CharacterStat);
		CharacterStat->OnHPChanged.Broadcast(); // 체력바 업데이트를 위한 것.
	}
	
	FName WeaponSocket(TEXT("FPSGunSocket"));
	CurWeapon = GetWorld()->SpawnActor<AFPSNormalGun>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (nullptr != CurWeapon)
	{
		CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
	}

	ProjectileClass = AProjectile::StaticClass();

	
}

void AFPSCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AnimInstance = Cast<UFPSAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr != AnimInstance)
	{
		//AnimInstance->OnMontageEnded.AddDynamic(this, &AFPSCharacter::OnFireMontageEnded);
	}
	

	// 체력이 0이 되었을 때 처리
	CharacterStat->OnHPIsZero.AddLambda([this]()->void {
		AnimInstance->SetDeadAnim();
		SetActorEnableCollision(false);
	});
}

float AFPSCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, 
	AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CharacterStat->SetDamage(FinalDamage);
	CharacterStat->OnHPChanged.Broadcast();
	return FinalDamage;
}

void AFPSCharacter::SetCameraMode(ECameraMode NewMode)
{
	CurMode = NewMode;

	switch (CurMode)
	{
	case ECameraMode::EXPLORE:
		SpringArm->TargetArmLength = 10000.0f;
		SpringArm->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

		break;
	case ECameraMode::FPS:
		SpringArm->TargetArmLength = 120.0f;
		SpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 50.0f, 15.0f + BaseEyeHeight), FRotator(60.0f, -45.0f, 0.0f));
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

		break;
	}
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	switch (CurMode)
	{
	case ECameraMode::EXPLORE:
		if (DirectionToMove.SizeSquared() > 0.0f)
		{
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
			AddMovementInput(DirectionToMove);
		}
		break;
	}
}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &AFPSCharacter::DoCrouch);
	PlayerInputComponent->BindAction(TEXT("ViewChange"), EInputEvent::IE_Pressed, this, &AFPSCharacter::ViewChange);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AFPSCharacter::Fire);
	PlayerInputComponent->BindAction(TEXT("UseSlot1"), EInputEvent::IE_Pressed, this, &AFPSCharacter::UseSlot1);
	

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AFPSCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AFPSCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AFPSCharacter::LookUp);
}

void AFPSCharacter::OnFireMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	/*if (true == IsAttacking)
	{
		IsAttacking = false;
	}*/
}

void AFPSCharacter::MoveForward(float Value)
{
	switch (CurMode)
	{
	case ECameraMode::EXPLORE:
		DirectionToMove.X = Value;
		break;
	case ECameraMode::FPS:
		AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X), Value);
		break;
	}
	
}

void AFPSCharacter::MoveRight(float Value)
{
	switch (CurMode)
	{
	case ECameraMode::EXPLORE:
		DirectionToMove.Y = Value;
		break;
	case ECameraMode::FPS:
		AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y), Value);
		break;
	}
	
}

void AFPSCharacter::LookUp(float Value)
{
	switch (CurMode)
	{
	case ECameraMode::FPS:
		AddControllerPitchInput(Value);
		break;
	}
}

void AFPSCharacter::Turn(float Value)
{
	switch (CurMode)
	{
	case ECameraMode::FPS:
		AddControllerYawInput(Value);
		break;
	}
}

void AFPSCharacter::DoCrouch()
{
	CanCrouch() ? Crouch() : UnCrouch();
}

void AFPSCharacter::ViewChange()
{
	switch (CurMode)
	{
	case ECameraMode::EXPLORE:
		SetCameraMode(ECameraMode::FPS);
		break;
	case ECameraMode::FPS:
		SetCameraMode(ECameraMode::EXPLORE);
		break;
	}
}

void AFPSCharacter::Fire()
{
	//if (true == IsAttacking) return;

	SetCameraMode(ECameraMode::FPS);
	AnimInstance = Cast<UFPSAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance) return;
	AnimInstance->PlayFireMontage();
	//IsAttacking = true;

	if (ProjectileClass)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		// MuzzleOffset을 카메라 스페이스에서 월드 스페이스로 변환
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRotation;
		// 조준을 약간 윗쪽으로 올려준다.
		MuzzleRotation.Pitch += 10.0f;
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
			// 총구 위치에 발사체를 스폰시킨다.
			AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				if(!Attack_Sound->IsPlaying())
					Attack_Sound->Play();
				// 총알 공격력 설정
				Projectile->SetAttack(CharacterStat->GetAttack());
				// 발사 방향을 알아냄.
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}

void AFPSCharacter::UseSlot1()
{
	if (FPSPlayerController->GetHUDWidget()->Slot1_DeleteCount())
		CharacterStat->AddHP(50.0f);
}

void AFPSCharacter::UseSlot2()
{
	if (IsInteract)
	{
		if (FPSPlayerController->GetHUDWidget()->Slot2_DeleteCount())
		{

		}
	}
}

void AFPSCharacter::Interact()
{
	IsInteract = true;
}

void AFPSCharacter::NoInteract()
{
	IsInteract = false;
}

bool AFPSCharacter::IsOpenPortal()
{
	if (FPSPlayerController->GetHUDWidget()->Slot2_DeleteCount())
		return true;

	return false;
}

