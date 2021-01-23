// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MonsterWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALFPS_API UMonsterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(class UFPSCharacterStatComponent* NewCharacterStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

private:
	TWeakObjectPtr<class UFPSCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
		class UProgressBar* HPProgressBar;
};
