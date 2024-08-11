// Fill out your copyright notice in the Description page of Project Settings.


#include "CH_GoWClone/Enemy/Enemy.h"
#include <Components/CapsuleComponent.h>


// Sets default values
AEnemy::AEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	RootComponent = Root;*/

	/*UCapsuleComponent* capsuleMesh = CreateDefaultSubobject<UCapsuleComponent>(FName("Capsule"));
	RootComponent = capsuleMesh;*/

	HostileMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Enemy"));
	
	//HostileMesh->SetupAttachment(capsuleMesh);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::KillEnemy()
{
	//Play Ragdoll

	HostileMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	HostileMesh->SetSimulatePhysics(true);
	//HostileMesh->WakeAllRigidBodies();

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, "Enemy has died");

	FTimerHandle DeathTimeHandle;
	GetWorldTimerManager().SetTimer(DeathTimeHandle, this, &AEnemy::DestroyEnemy, 2.0f, false);
}

void AEnemy::DamageEnemy(float Damage)
{
	EnemyHealth -= Damage;

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, "Enemy is losing HP");

	if (EnemyHealth <= 0)
	{
		KillEnemy();
	}
}

void AEnemy::DestroyEnemy()
{
	Destroy();
}

