// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealFPS.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "PickupItem.generated.h"

USTRUCT(BlueprintType)
struct FItemInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	FItemInfo()
	{
		ItemName = FText::FromString("Name");
		ItemGold = 0;
		ItemDescription = FText::FromString("This Item is ....");
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* ItemThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ItemGold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText ItemDescription;
};

UCLASS()
class UNREALFPS_API APickupItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
