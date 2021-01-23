// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/HUD.h"
#include "TitleMenu_HUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREALFPS_API ATitleMenu_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ATitleMenu_HUD();
	void BeginPlay() override;

private:
	TSubclassOf<class UUserWidget> uiBPClass;
	UUserWidget* uiWidget;
};
