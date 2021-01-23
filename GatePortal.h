// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "GatePortal.generated.h"

UCLASS()
class UNREALFPS_API AGatePortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGatePortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEffectFinished(UParticleSystemComponent* PSystem);

private:
	UPROPERTY()
		UParticleSystemComponent* Lock_Effect;

	UPROPERTY()
		UParticleSystemComponent* Open_Effect;

	UPROPERTY()
		USphereComponent* Trigger;

	UPROPERTY()
		UBoxComponent* Barrier;
};
