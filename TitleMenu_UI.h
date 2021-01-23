// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleMenu_UI.generated.h"

/**
 * 
 */
UCLASS()
class UNREALFPS_API UTitleMenu_UI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadOnly)
		class UButton* Btn_Start = nullptr;

	UPROPERTY(BlueprintReadOnly)
		class UButton* Btn_Exit = nullptr;

private:
	UFUNCTION()
		void Btn_StartGame_Clicked();

	UFUNCTION()
		void Btn_ExitGame_Clicked();
};
