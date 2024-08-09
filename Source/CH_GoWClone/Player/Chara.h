#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Chara.generated.h"

UCLASS()
class CH_GOWCLONE_API AChara : public ACharacter
{
	GENERATED_BODY()
//-------------------------MY CODE-------------------------
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Cam;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;
//-------------------------MY CODE-------------------------

public:
	// Sets default values for this character's properties
	AChara();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

//-------------------------MY CODE-------------------------
protected:

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;
	
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	class UInputAction* CharaMove;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	class UInputAction* CharaJump;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	class UInputAction* CharaLook;

	void MoveChara(const FInputActionValue& InputValue);
	void LookChara(const FInputActionValue& InputValue);
	void JumpChara();
//-------------------------MY CODE-------------------------
};
