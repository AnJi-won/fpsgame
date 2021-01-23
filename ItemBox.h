// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBox.generated.h"

UCLASS()
class UNREALFPS_API AItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void OnEffectFinished(UParticleSystemComponent* PSystem);

	void Interact();

public:
	UPROPERTY(VisibleAnywhere, Category = Box)
		UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = Box)
		UStaticMeshComponent* BoxMesh;

	UPROPERTY(EditAnywhere, Category = ItemType)
		int32 ItemTypeNum;

	UPROPERTY(VisibleAnywhere, Category=Effect)
		UParticleSystemComponent* Effect;

	UPROPERTY(VisibleAnywhere, Category = Sound)
		UAudioComponent* Sound;

	bool IsOpen;
};
