// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleMenu_GameMode.h"
#include "TitleMenu_HUD.h"
#include "TitleMenu_Controller.h"

ATitleMenu_GameMode::ATitleMenu_GameMode()
{
	HUDClass = ATitleMenu_HUD::StaticClass();
	DefaultPawnClass = nullptr;
	PlayerControllerClass = ATitleMenu_Controller::StaticClass();
}
