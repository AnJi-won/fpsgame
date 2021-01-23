// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPSHUDWidget.generated.h"


/**
 * 
 */
UCLASS()
class UNREALFPS_API UFPSHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFPSHUDWidget(const class FObjectInitializer& ObjectInitializer);
	void BindCharacterStat(class UFPSCharacterStatComponent* CharacterStat);
	void Slot1_AddCount();
	void Slot2_AddCount();
	bool Slot1_DeleteCount();
	bool Slot2_DeleteCount();

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterStat();
	

public:
	UFUNCTION()
		void Btn_Pause_Clicked();
	
private:
	TWeakObjectPtr<class UFPSCharacterStatComponent> CurrentCharacterStat;
	
	UPROPERTY()
		class UProgressBar* HPBar;

	UPROPERTY()
		class UButton* Btn_Pause;

	bool IsPause = false;

	UPROPERTY()
		class UInvenSlotWidget* Slot1;

	UPROPERTY()
		class UInvenSlotWidget* Slot2;
};
