// Fill out your copyright notice in the Description page of Project Settings.


#include "CH_GoWClone/Weapon/Gun.h"
#include <Kismet/GameplayStatics.h>
#include "CH_GoWClone/Player/Chara.h"
#include "CH_GoWClone/Enemy/Enemy.h"


// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	RootComponent = Root;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	WeaponMesh->SetupAttachment(Root);
	//Spawn the gun in the player's hands, whereever the socket is. 

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Upon being fired, spawn and fire a bullet in a specific direction.
void AGun::Shoot(const FVector& StartTrace, const FVector& EndTrace)
{
	//RayCast Code
	FHitResult* Hit = new FHitResult();

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = false;

	if (GetWorld()->LineTraceSingleByChannel(*Hit, StartTrace, EndTrace, ECC_Visibility, QueryParams))
	{
		if (ImpactParticles != NULL)
		{
			//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, FTransform(Hit.ImpactNormal.Rotation(), Hit.ImpactPoint));
		}
		else
		{
			DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Emerald, false, 2.0f);
		}

		AEnemy* HitEnemy = Cast<AEnemy>(Hit->GetActor());

		if (HitEnemy != NULL && !HitEnemy->IsPendingKillPending())
		{
			HitEnemy->DamageEnemy(DamagePerShot);
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, "Hit Enemy");

		}
	}

	//Bullets code
	if (CurrentBulletCount > 0)
	{
		CurrentBulletCount--;
	}
	else if (CurrentBulletCount <= 0)
	{
		//Print some kinda message on debug.
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Out Of Ammo");
	}

	//Muzzle VFX code
	if (MuzzleParticles != NULL)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleParticles, CurrentOwner->GetMesh()->GetSocketTransform(FName("Muzzle")));
	}

	//SFX code
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	//Anim code
	if (FireAnimation != NULL)
	{
		UAnimInstance* AnimInstance = CurrentOwner->GetMesh()->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.0f);
		}
	}
}

//Upon being called, play reload animation and reset Bullet Count to max number.
void AGun::Reload()
{
	//Play a reload animation.
	if (CurrentAmmoCount != 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Reloading");
		CurrentBulletCount = MaxBulletsInMagazine;
		CurrentAmmoCount -= CurrentBulletCount;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Reload Complete");

		if (CurrentAmmoCount <= 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "No More Ammo Reserves");
		}
	}

	//Check if the animation is done playing.
		//If yes, then reset the CurrentBulletCount to be equal to MaxBulletCount.
		//Subtract the MaxBullet Count from the CurrentAmmoCount.
}

//Upon being called, move camera position to just above the gun.
void AGun::AimDownSights()
{
	//While aiming button is held, move the camera to the position of the gun's sights

	//When released, move the camera back to its original position.
}

//Upon being called, refill this gun's ammo instantly without animations to max capacity, including reserves.
void AGun::RefillAmmoFromPickup()
{

}

