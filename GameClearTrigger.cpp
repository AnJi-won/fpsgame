// Fill out your copyright notice in the Description page of Project Settings.


#include "GameClearTrigger.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameClearTrigger::AGameClearTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AGameClearTrigger::OnOverlapBegin);
	Trigger->SetCollisionProfileName(TEXT("GameClearTrigger"));
}

// Called when the game starts or when spawned
void AGameClearTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameClearTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameClearTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* Pawn = Cast<APawn>(OtherActor);
	if (Pawn)
	{
		UGameplayStatics::OpenLevel(this, "TitleMenu");
	}
}

