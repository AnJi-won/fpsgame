// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterWidget.h"
#include "FPSCharacterStatComponent.h"
#include "Components/ProgressBar.h"

void UMonsterWidget::BindCharacterStat(UFPSCharacterStatComponent* NewCharacterStat)
{
	if (nullptr == NewCharacterStat) return;

	CurrentCharacterStat = NewCharacterStat;
	NewCharacterStat->OnHPChanged.AddUObject(this, &UMonsterWidget::UpdateHPWidget);
}

void UMonsterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));

	if(nullptr != HPProgressBar)
		UpdateHPWidget();
}

void UMonsterWidget::UpdateHPWidget()
{
	if (CurrentCharacterStat.IsValid())
	{
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
		}
	}
}
