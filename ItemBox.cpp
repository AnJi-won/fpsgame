// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBox.h"
#include "FPSCharacter.h"

// Sets default values
AItemBox::AItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));
	Sound = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound"));

	RootComponent = Trigger;
	BoxMesh->SetupAttachment(RootComponent);
	Effect->SetupAttachment(RootComponent);

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AItemBox::OnOverlapBegin);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AItemBox::OnOverlapEnd);
	Trigger->SetBoxExtent(FVector(100.0f, 100.0f, 70.0f));
	Trigger->SetCollisionProfileName(TEXT("ItemBox"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MESH_BOX(
		TEXT("/Game/StarterBundle/ModularScifiHallways/Meshes/SM_Crate_A.SM_Crate_A"));
	if (MESH_BOX.Succeeded())
	{
		BoxMesh->SetStaticMesh(MESH_BOX.Object);
	}
	BoxMesh->SetRelativeLocation(FVector(-30.0f, -50.0f, -55.0f));
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_SYSTEM(
		TEXT("/Game/InfinityBladeEffects/Effects/FX_Treasure/Chest/P_TreasureChest_CallOut.P_TreasureChest_CallOut"));
	if (P_SYSTEM.Succeeded())
	{
		Effect->SetTemplate(P_SYSTEM.Object);
		Effect->bAutoActivate = false;
	}

	static ConstructorHelpers::FObjectFinder<USoundWave> SOUND_OPEN(
		TEXT("/Game/Sound/ItemGetSound.ItemGetSound"));
	if (SOUND_OPEN.Succeeded())
	{
		Sound->SetSound(SOUND_OPEN.Object);
		Sound->bAutoActivate = false;
		Sound->SetVolumeMultiplier(3.0f);
	}

	ItemTypeNum = 1;
	IsOpen = false;
}

// Called when the game starts or when spawned
void AItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	
}

void AItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AItemBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (!IsOpen && OtherActor->IsA(AFPSCharacter::StaticClass()))
	{
		IsOpen = true;
		AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor);
		
		Character->GetItem(ItemTypeNum);
		Effect->Activate(true);
		Sound->Play();
		BoxMesh->SetHiddenInGame(true, true);
		SetActorEnableCollision(false);
		Effect->OnSystemFinished.AddDynamic(this, &AItemBox::OnEffectFinished);
	}
}


void AItemBox::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void AItemBox::OnEffectFinished(UParticleSystemComponent* PSystem)
{
	Destroy();
}

void AItemBox::Interact()
{
	
}


