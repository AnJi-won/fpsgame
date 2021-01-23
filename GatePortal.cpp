// Fill out your copyright notice in the Description page of Project Settings.


#include "GatePortal.h"
#include "FPSCharacter.h"

// Sets default values
AGatePortal::AGatePortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Lock_Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LockedPortalEffect"));
	Open_Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("OpenPortalEffect"));
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	Barrier = CreateDefaultSubobject<UBoxComponent>(TEXT("Barrier"));

	RootComponent = Trigger;
	Lock_Effect->SetupAttachment(RootComponent);
	Open_Effect->SetupAttachment(RootComponent);
	Barrier->SetupAttachment(RootComponent);

	Trigger->InitSphereRadius(200.0f);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AGatePortal::OnOverlapBegin);
	Trigger->SetCollisionProfileName(TEXT("GateTrigger"));


	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_LOCK(TEXT(
		"/Game/InfinityBladeEffects/Effects/FX_Gates/ICE/P_Gate_Ice_Locked_01.P_Gate_Ice_Locked_01"));
	if (P_LOCK.Succeeded())
	{
		Lock_Effect->SetTemplate(P_LOCK.Object);
		Lock_Effect->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		Lock_Effect->bAutoActivate = true;
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_OPEN(TEXT(
		"/Game/InfinityBladeEffects/Effects/FX_Gates/ICE/P_Gate_Ice_Opening_01.P_Gate_Ice_Opening_01"));
	if (P_OPEN.Succeeded())
	{
		Open_Effect->SetTemplate(P_OPEN.Object);
		Open_Effect->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		Open_Effect->bAutoActivate = false;
	}

	Barrier->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	Barrier->SetRelativeLocation(FVector(0.f, -150.f, 0.0f));
	Barrier->SetBoxExtent(FVector(300.0f, 100.0f, 500.0f));
	Barrier->SetCollisionProfileName(TEXT("Portal"));
	
}

// Called when the game starts or when spawned
void AGatePortal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGatePortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGatePortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Character = Cast<AFPSCharacter>(OtherActor);
	if (Character && Character->IsOpenPortal())
	{
		Lock_Effect->Activate(false);
		Open_Effect->Activate(true);
		Open_Effect->OnSystemFinished.AddDynamic(this, &AGatePortal::OnEffectFinished);
		SetActorEnableCollision(false);
		
	}
}

void AGatePortal::OnEffectFinished(UParticleSystemComponent* PSystem)
{
	Destroy();
}

