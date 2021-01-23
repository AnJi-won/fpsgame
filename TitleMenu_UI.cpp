// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleMenu_UI.h"
#include "Components/Button.h"

void UTitleMenu_UI::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Start = Cast<UButton>(GetWidgetFromName(TEXT("Button_Start")));
	Btn_Exit = Cast<UButton>(GetWidgetFromName(TEXT("Button_Exit")));

	if (Btn_Start)
	{
		Btn_Start->OnClicked.AddDynamic(this, &UTitleMenu_UI::Btn_StartGame_Clicked);
	}

	if (Btn_Exit)
	{
		Btn_Exit->OnClicked.AddDynamic(this, &UTitleMenu_UI::Btn_ExitGame_Clicked);
	}
}

void UTitleMenu_UI::Btn_StartGame_Clicked()
{
	UGameplayStatics::OpenLevel(this, "/Game/MyMaps/InGameMap");
}

void UTitleMenu_UI::Btn_ExitGame_Clicked()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
