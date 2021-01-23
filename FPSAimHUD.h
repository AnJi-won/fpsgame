// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPSAimHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREALFPS_API AFPSAimHUD : public AHUD
{
	GENERATED_BODY()

public:
	AFPSAimHUD();
	virtual void DrawHUD() override;
	
protected:
	UPROPERTY(EditDefaultsOnly)
		UTexture2D* AimTexture;
};
