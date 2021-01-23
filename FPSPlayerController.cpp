// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayerController.h"
#include "FPSHUDWidget.h"
#include "ItemSlotWidget.h"

AFPSPlayerController::AFPSPlayerController()
{
	static ConstructorHelpers::FClassFinder<UFPSHUDWidget> STAT_HUD(
		TEXT("/Game/UI/UI_Stat.UI_Stat_C"));
	if (STAT_HUD.Succeeded())
	{
		HUDWidgetClass = STAT_HUD.Class;
	}

	
}

UFPSHUDWidget* AFPSPlayerController::GetHUDWidget() const
{
	return HUDWidget;
}

void AFPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	HUDWidget = CreateWidget<UFPSHUDWidget>(this, HUDWidgetClass);
	HUDWidget->AddToViewport();

	
}

void AFPSPlayerController::SetupInputComponent()
{
	APlayerController::SetupInputComponent();

	
}

