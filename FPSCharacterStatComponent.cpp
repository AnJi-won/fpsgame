// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacterStatComponent.h"

// Sets default values for this component's properties
UFPSCharacterStatComponent::UFPSCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	// ...
	CurrentHP = 0.f;
	MaxHP = 0.f;
	Attack = 0.f;
}


// Called when the game starts
void UFPSCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UFPSCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
}


// Called every frame
void UFPSCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFPSCharacterStatComponent::SetCharacterStat(float _MaxHP, float _Attack)
{
	this->MaxHP = _MaxHP;
	this->CurrentHP = _MaxHP;
	this->Attack = _Attack;
}

void UFPSCharacterStatComponent::SetDamage(float NewDamage)
{
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, MaxHP));
}

void UFPSCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

void UFPSCharacterStatComponent::AddHP(float AddHP)
{
	SetHP(FMath::Clamp<float>(CurrentHP + AddHP, 0.0f, MaxHP));
	OnHPChanged.Broadcast();
}

float UFPSCharacterStatComponent::GetAttack()
{
	return Attack;
}

float UFPSCharacterStatComponent::GetHPRatio()
{
	return (MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / MaxHP);
}

