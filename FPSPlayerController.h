// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALFPS_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AFPSPlayerController();

	class UFPSHUDWidget* GetHUDWidget() const;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UFPSHUDWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UItemSlotWidget> ItemSlotWidgetClass;

private:
	UPROPERTY()
		class UFPSHUDWidget* HUDWidget;

	UPROPERTY()
		class UItemSlotWidget* ItemSlotWidget;
};
