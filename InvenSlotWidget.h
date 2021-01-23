// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine/DataTable.h"
#include "Blueprint/UserWidget.h"
#include "InvenSlotWidget.generated.h"

UENUM(BlueprintType)
enum EItemType
{
	ITEM_None				UMETA(DisplayName = "None"),
	ITEM_Potion			UMETA(DisplayName = "Potion"),
	ITEM_Quest		UMETA(DisplayName = "Quest")
};

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

public:
	FItemData()
		: Name(TEXT("")), Texture(nullptr), Type(EItemType::ITEM_None), Count(0)
	{}

	virtual void Clear() {};
	virtual void Use(ACharacter* player) {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Texture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EItemType> Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Count;

	
};

UENUM(BlueprintType)
enum ESlotType
{
	SLOT_None			UMETA(DisplayName = "None"),
	SLOT_Item			UMETA(DisplayName = "Item"),
	SLOT_Skill				UMETA(DisplayName = "Skill"),
	SLOT_Quick			UMETA(DisplayName = "Quick"),
	SLOT_Q_Item		UMETA(DisplayName = "Q_Item"),
	SLOT_Q_Skill		UMETA(DisplayName = "Q_Skill")
};

/**
 * 
 */
UCLASS()
class UNREALFPS_API UInvenSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	UInvenSlotWidget(const class FObjectInitializer& ObjectInitializer);
	void SetType(EItemType ItemType);
	void SetSlotTexture();
	void AddCount();
	bool DeleteCount();
	void UpdateSlot();
	void SetCount(int NewCount);
	int GetCount() { return Count; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMax = 31, UIMin = -1))
		int Slotnum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int Count;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TEnumAsByte<EItemType> Type;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* Img;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Text;

	UPROPERTY()
		class UDataTable* ItemDataTable;

	UPROPERTY()
		class UTexture2D* Texture_Potion;

	UPROPERTY()
		class UTexture2D* Texture_Quest;
};
