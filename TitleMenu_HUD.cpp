// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleMenu_HUD.h"
#include "Blueprint/UserWidget.h"

ATitleMenu_HUD::ATitleMenu_HUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ui(TEXT("/Game/UI/UI_TitleMenu.UI_TitleMenu_C"));
	if (ui.Succeeded())
	{
		uiBPClass = ui.Class;
	}
}

void ATitleMenu_HUD::BeginPlay()
{
	Super::BeginPlay();

	if (uiBPClass)
	{
		uiWidget = CreateWidget<UUserWidget>(GetWorld(), uiBPClass);
		if (uiWidget)
		{
			uiWidget->AddToViewport();
		}
	}
}
