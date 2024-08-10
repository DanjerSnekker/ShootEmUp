// Fill out your copyright notice in the Description page of Project Settings.


#include "CH_GoWClone/Weapon/Bullet.h"


// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>("ProjectileSceneComponent");
	}

	if (!CollisionComponent)
	{
		//Using a sphere to represent collision for the bullets.
		CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");

		//Giving the sphere bullet a radius of 5 [Change if too big)
		CollisionComponent->InitSphereRadius(5.0f);	

		RootComponent = CollisionComponent;
	}

	if (!BulletMoveComponent)
	{
		//Use this component to actually move the bullet.
		BulletMoveComponent = CreateDefaultSubobject<UProjectileMovementComponent>("BulletMoveComponent");
		BulletMoveComponent->SetUpdatedComponent(CollisionComponent);
		BulletMoveComponent->InitialSpeed = 3000.0f;
		BulletMoveComponent->MaxSpeed = 3000.0f;
		BulletMoveComponent->bRotationFollowsVelocity = true;
		BulletMoveComponent->Bounciness = false;
		BulletMoveComponent->ProjectileGravityScale = 0.0f;
	}
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Determines the bullet's velocity in the firing direction.
void ABullet::Fire(const FVector& ShootDir)
{
	BulletMoveComponent->Velocity = ShootDir * BulletMoveComponent->InitialSpeed;
}

