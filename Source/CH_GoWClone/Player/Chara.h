#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Chara.generated.h"

UCLASS()
class CH_GOWCLONE_API AChara : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AChara();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	void MoveForward(float InputVal);
	void MoveRight(float InputVal);

	void Turn(float InputVal);
	void LookUp(float InputVal);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
