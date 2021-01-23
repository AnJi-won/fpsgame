// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSNormalGun.h"

AFPSNormalGun::AFPSNormalGun()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WEAPON_MESH(
		TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/KA74U/SK_KA74U_X.SK_KA74U_X"));
	if (WEAPON_MESH.Succeeded())
	{
		WeaponMesh->SetSkeletalMesh(WEAPON_MESH.Object);
	}
	WeaponMesh->SetCollisionProfileName(TEXT("NoCollision"));
}