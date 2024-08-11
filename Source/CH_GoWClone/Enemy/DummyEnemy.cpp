// Fill out your copyright notice in the Description page of Project Settings.


#include "CH_GoWClone/Enemy/DummyEnemy.h"


// Sets default values
ADummyEnemy::ADummyEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//HostileMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Enemy"));

}

// Called when the game starts or when spawned
void ADummyEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADummyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADummyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADummyEnemy::KillEnemy()
{
	//Play Ragdoll

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
	//HostileMesh->WakeAllRigidBodies();

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, "Enemy has died");

	FTimerHandle DeathTimeHandle;
	GetWorldTimerManager().SetTimer(DeathTimeHandle, this, &ADummyEnemy::DestroyEnemy, 2.0f, false);
}

void ADummyEnemy::DamageEnemy(float Damage)
{
	EnemyHealth -= Damage;

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, "Enemy is losing HP");

	if (EnemyHealth <= 0)
	{
		KillEnemy();
	}
}

void ADummyEnemy::DestroyEnemy()
{
	Destroy();
}