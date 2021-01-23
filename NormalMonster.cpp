// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalMonster.h"
#include "Components/WidgetComponent.h"
#include "MonsterWidget.h"
#include "FPSCharacterStatComponent.h"
#include "MonsterAnimInstance.h"
#include "MonsterAIController.h"
#include "FPSCharacter.h"

ANormalMonster::ANormalMonster()
{
	IsAttacking = false;
	DeadTimer = 5.0f;

	Dead_Sound = CreateDefaultSubobject<UAudioComponent>(TEXT("DeadSound"));

	static ConstructorHelpers::FObjectFinder<USoundWave> SOUND_DEAD(
		TEXT("/Game/Sound/MonsterDead.MonsterDead"));
	if (SOUND_DEAD.Succeeded())
	{
		Dead_Sound->SetSound(SOUND_DEAD.Object);
		Dead_Sound->bAutoActivate = false;
		Dead_Sound->SetVolumeMultiplier(3.0f);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Normal(
		TEXT("/Game/ODSMannequin/FemaleMannequin/Character/Mesh/SK_FemaleMannequin.SK_FemaleMannequin"));
	if (SK_Normal.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Normal.Object);
	}
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_Normal(
		TEXT("/Game/Animation/AnimBP_FemaleMonster.AnimBP_FemaleMonster_C"));
	if (ANIM_Normal.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_Normal.Class);
	}

	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HPBar(
		TEXT("/Game/UI/UI_HPBar.UI_HPBar_C"));
	if (UI_HPBar.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HPBar.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
		HPBarWidget->SetHiddenInGame(true);
	}

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(GetCapsuleComponent());
	CollisionSphere->SetCollisionProfileName(TEXT("HiddenMonsterUI"));
	CollisionSphere->InitSphereRadius(600.0f);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ANormalMonster::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &ANormalMonster::OnOverlapEnd);

	//GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
}

void ANormalMonster::BeginPlay()
{
	AMonster::BeginPlay();
	CharacterStat->SetCharacterStat(100.0f, 10.0f);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	auto MonsterWidget = Cast<UMonsterWidget>(HPBarWidget->GetUserWidgetObject());
	if (nullptr != MonsterWidget)
	{
		MonsterWidget->BindCharacterStat(CharacterStat);
	}

	MonsterAIController = Cast<AMonsterAIController>(GetController());
	if (nullptr != MonsterAIController)
	{
		MonsterAIController->RunAI();
	}
	
}

void ANormalMonster::PostInitializeComponents()
{
	AMonster::PostInitializeComponents();

	

	MonsterAnim = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr != MonsterAnim)
	{
		MonsterAnim->OnMontageEnded.AddDynamic(this, &ANormalMonster::OnAttackMontageEnded);
		MonsterAnim->OnHitCheck.AddUObject(this, &ANormalMonster::AttackCheck);
	}

	// 체력이 0이 되었을 때 처리
	CharacterStat->OnHPIsZero.AddLambda([this]()->void {
		MonsterAnim->SetDeadAnim();
		SetActorEnableCollision(false);
		MonsterAIController->StopAI();
		ToggleUI(true);
		Dead_Sound->Play();
		GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([this]()->void {
			Destroy();
		}), DeadTimer, false);
	});
}

void ANormalMonster::Tick(float DeltaTime)
{
	AMonster::Tick(DeltaTime);
}

void ANormalMonster::Attack()
{
	if (IsAttacking) return;

	MonsterAnim->PlayAttackMontage();
	IsAttacking = true;
	
}

void ANormalMonster::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 200.0f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3,
		FCollisionShape::MakeSphere(50.0f),
		Params);

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hit!!"));

			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(CharacterStat->GetAttack(), DamageEvent, GetController(), this);
		}
	}
}

void ANormalMonster::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	OnAttackEnd.Broadcast();
	IsAttacking = false;
}

void ANormalMonster::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AFPSCharacter::StaticClass()))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CollisionBegin"));
		ToggleUI(false);
	}
}

void ANormalMonster::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AFPSCharacter::StaticClass()))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("End"));
		ToggleUI(true);
	}
}

void ANormalMonster::ToggleUI(bool IsHiddenUI)
{
	if (HPBarWidget)
	{
		HPBarWidget->SetHiddenInGame(IsHiddenUI);
	}
}
