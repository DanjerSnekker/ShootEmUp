#include "CH_GoWClone/Player/Chara.h"
#include "Camera/CameraComponent.h"
#include "CH_GoWClone/Components/Health.h"

// Sets default values. Runs when UE is launched.
AChara::AChara()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCam"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AChara::BeginPlay()
{
	Super::BeginPlay();
	
}

void AChara::MoveForward(float InputVal)
{
	FVector ForwardDir = GetActorForwardVector();
	AddMovementInput(ForwardDir, InputVal);
}

void AChara::MoveRight(float InputVal)
{
	FVector RightDir = GetActorRightVector();
	AddMovementInput(RightDir, InputVal);
}

void AChara::Turn(float InputVal)
{
	AddControllerYawInput(InputVal);
}

void AChara::LookUp(float InputVal)
{
	AddControllerPitchInput(InputVal);
}

// Called every frame
void AChara::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChara::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Spacebar", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAxis("MoveForward", this, &AChara::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AChara::MoveRight);

	PlayerInputComponent->BindAxis("TurnCamera", this, &AChara::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AChara::LookUp);
}

