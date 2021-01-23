// Fill out your copyright notice in the Description page of Project Settings.


#include "InvenSlotWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

UInvenSlotWidget::UInvenSlotWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> PotionTEX(TEXT("/Game/Item/HPPotion.HPPotion"));
	if (PotionTEX.Succeeded())
	{
		Texture_Potion = PotionTEX.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> QUESTTEX(TEXT("/Game/Item/QuestItem.QuestItem"));
	if (QUESTTEX.Succeeded())
	{
		Texture_Quest = QUESTTEX.Object;
	}

	
}

void UInvenSlotWidget::SetType(EItemType ItemType)
{
	Type = ItemType;

	SetSlotTexture();
}

void UInvenSlotWidget::SetSlotTexture()
{
	switch (Type)
	{
	case EItemType::ITEM_None:
		break;
	case EItemType::ITEM_Potion:
		Img->SetBrushFromTexture(Texture_Potion);
		break;
	case EItemType::ITEM_Quest:
		Img->SetBrushFromTexture(Texture_Quest);
		break;
	}
}

void UInvenSlotWidget::AddCount()
{
	Count++;
	UpdateSlot();
}

bool UInvenSlotWidget::DeleteCount()
{
	if (Count <= 0)
		return false;

	Count--;
	UpdateSlot();
	return true;
}

void UInvenSlotWidget::UpdateSlot()
{
	if (Text)
	{
		Text->SetText(FText::FromString(FString::FromInt(Count)));
	}
}

void UInvenSlotWidget::SetCount(int NewCount)
{
	Count = NewCount;
	if (Text)
	{
		Text->SetText(FText::FromString(FString::FromInt(Count)));
	}
}

void UInvenSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Img = Cast<UImage>(GetWidgetFromName(TEXT("Img")));
	if (Img)
	{
		//SetType(EItemType::ITEM_Quest);
	}
	Text = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text")));
	if (Text)
	{
		Text->SetText(FText::FromString(FString::FromInt(Count)));
	}
	
	
}

