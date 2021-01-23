// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "FPSCharacterStatComponent.h"
#include "MonsterAIController.h"
#include "Components/WidgetComponent.h"


// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	CharacterStat = CreateDefaultSubobject< UFPSCharacterStatComponent>(TEXT("CharacterStat"));
	
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	HPBarWidget->SetupAttachment(GetMesh());
	
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonster::SetDamage(float NewDamage)
{
	if(nullptr != CharacterStat)
		CharacterStat->SetDamage(NewDamage);
}



