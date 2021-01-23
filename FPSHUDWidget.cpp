// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"
#include "FPSCharacterStatComponent.h"
#include "InvenSlotWidget.h"

UFPSHUDWidget::UFPSHUDWidget(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UFPSHUDWidget::BindCharacterStat(UFPSCharacterStatComponent* CharacterStat)
{
	if (nullptr != CharacterStat)
	{
		CurrentCharacterStat = CharacterStat;
		CharacterStat->OnHPChanged.AddUObject(this, &UFPSHUDWidget::UpdateCharacterStat);
	}
	
}

void UFPSHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	UpdateCharacterStat();

	Btn_Pause = Cast<UButton>(GetWidgetFromName(TEXT("Button_Pause")));
	if (Btn_Pause)
	{
		Btn_Pause->OnClicked.AddDynamic(this, &UFPSHUDWidget::Btn_Pause_Clicked);
	}

	Slot1 = Cast<UInvenSlotWidget>(GetWidgetFromName(TEXT("Slot01")));
	if (Slot1)
	{
		Slot1->SetType(EItemType::ITEM_Potion);
		Slot1->SetCount(5);
	}

	Slot2 = Cast<UInvenSlotWidget>(GetWidgetFromName(TEXT("Slot02")));
	if (Slot2)
	{
		Slot2->SetType(EItemType::ITEM_Quest);
		Slot2->SetCount(0);
	}
}

void UFPSHUDWidget::UpdateCharacterStat()
{
	if (nullptr != CurrentCharacterStat)
	{
		HPBar->SetPercent(CurrentCharacterStat->GetHPRatio());
	}
}

void UFPSHUDWidget::Slot1_AddCount()
{
	if (Slot1)
	{
		Slot1->AddCount();
	}
}

void UFPSHUDWidget::Slot2_AddCount()
{
	if (Slot2)
	{
		Slot2->AddCount();
	}
}

bool UFPSHUDWidget::Slot1_DeleteCount()
{
	return Slot1->DeleteCount();
}

bool UFPSHUDWidget::Slot2_DeleteCount()
{
	return Slot2->DeleteCount();
}

void UFPSHUDWidget::Btn_Pause_Clicked()
{
	IsPause = !IsPause;

	auto MyPlayerController = Cast<APlayerController>(GetOwningPlayer());
	MyPlayerController->SetPause(IsPause);
}
