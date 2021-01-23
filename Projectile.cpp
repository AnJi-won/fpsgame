// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Monster.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));
	CollisionComponent->InitSphereRadius(10.0f);

	RootComponent = CollisionComponent;
	Effect->SetupAttachment(RootComponent);
	
	//CollisionComponent->SetCollisionProfileName(TEXT("Projectile"));
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
	
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 5000.0f;
	ProjectileMovementComponent->MaxSpeed = 5000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;

	InitialLifeSpan = 3.0f;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_SYSTEM(
		TEXT("/Game/InfinityBladeEffects/Effects/FX_Combat_Base/Impact/P_Impact_Player_Fire_Strong.P_Impact_Player_Fire_Strong"));
	if (P_SYSTEM.Succeeded())
	{
		Effect->SetTemplate(P_SYSTEM.Object);
		Effect->bAutoActivate = false;
	}
	////// 테스트 메시 ///////////////////
	TestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TestMesh"));
	TestMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TEST_MESH(
		TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/Ammunition/SM_Shell_12Gauge.SM_Shell_12Gauge"));
	if (TEST_MESH.Succeeded())
		TestMesh->SetStaticMesh(TEST_MESH.Object);
	TestMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	SetActorScale3D(FVector(3.0f, 3.0f, 3.0f));

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

//void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
//	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
//{
//	
//	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
//	{
//		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Hit!"));
//	}
//}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMonster::StaticClass()))
	{
		AMonster* Monster = Cast<AMonster>(OtherActor);
		
		Monster->SetDamage(ProjectileAttack);
		
		Effect->Activate(true);
		SetActorEnableCollision(false);
		Effect->OnSystemFinished.AddDynamic(this, &AProjectile::OnEffectFinished);
	}
}

void AProjectile::OnEffectFinished(UParticleSystemComponent* PSystem)
{
	Destroy();
}

