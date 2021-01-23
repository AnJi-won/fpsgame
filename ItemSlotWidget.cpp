// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"
#include "Components/Image.h"

void UItemSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ItemIcon = Cast<UImage>(GetWidgetFromName(TEXT("ItemIcon")));
	if (ItemIcon)
	{
		static ConstructorHelpers::FObjectFinder<UTexture2D> IconTex(
			TEXT("/Game/Item/HPPotion.HPPotion"));
		if(IconTex.Succeeded())
			ItemIcon->SetBrushFromTexture(IconTex.Object);
	}
}