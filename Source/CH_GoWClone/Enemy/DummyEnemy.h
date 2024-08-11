// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DummyEnemy.generated.h"

UCLASS()
class CH_GOWCLONE_API ADummyEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADummyEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void KillEnemy();

	void DamageEnemy(float dmg);

	void DestroyEnemy();

	UPROPERTY(VisibleAnywhere, Category = "Enemy Config")
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category = "Enemy Config")
	USkeletalMeshComponent* HostileMesh;

	UPROPERTY(EditAnywhere, Category = "Enemy Config")
	float EnemyHealth = 30.0f;

	bool isDying;
	
};
