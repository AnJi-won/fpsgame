// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameMode.h"
#include "FPSCharacter.h"
#include "FPSPlayerController.h"


AFPSGameMode::AFPSGameMode()
{
	DefaultPawnClass = AFPSCharacter::StaticClass();
	PlayerControllerClass = AFPSPlayerController::StaticClass();
	
}