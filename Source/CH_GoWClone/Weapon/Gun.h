// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class CH_GOWCLONE_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Range of the weapon.
	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	float WeaponRange = 10000.0f;

	void Shoot(const FVector& StartTrace, const FVector& EndTrace);

	void Reload();

	void AimDownSights();

	void RefillAmmoFromPickup();

protected:

	//Amount of dmg dealt per bullet.
	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	int DamagePerShot;

	//How much time should the script wait for the animation before actually reloading.
	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	float ReloadTime;

	//Maximum amount of bullets in a magazine.
	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	int MaxBulletsInMagazine;

	//Current amount of bullets in the magazine.
	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	int CurrentBulletCount;

	//Total amount of ammo the gun has, including reserves.
	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	int TotalAmmoCount;

	//Current amount of ammo the gun has, including reserves.
	UPROPERTY(EditAnywhere, Category = "Weapon Ifno")
	int CurrentAmmoCount;
	
	UPROPERTY(EditAnywhere, Category = "Weapon VFX & SFX")
	class USoundBase* FireSound;

	//Amount of dmg dealt per bullet.
	UPROPERTY(EditAnywhere, Category = "Weapon VFX & SFX")
	class UParticleSystem* MuzzleParticles;

	//Amount of dmg dealt per bullet.
	UPROPERTY(EditAnywhere, Category = "Weapon VFX & SFX")
	class UParticleSystem* ImpactParticles;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, Category = "Weapon VFX & SFX")
	class UAnimMontage* FireAnimation;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon Mesh")
	class USkeletalMeshComponent* GunMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon Mesh")
	USceneComponent* MuzzleLocation;
};
