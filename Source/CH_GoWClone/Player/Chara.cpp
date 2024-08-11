#include "CH_GoWClone/Player/Chara.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CH_GoWClone/Weapon/Gun.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AChara::AChara()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialize SpringArm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	//Initialize Camera
	Cam = CreateDefaultSubobject<UCameraComponent>("Camera");
	Cam->SetupAttachment(SpringArm);

	//Ensures camera rotation will rotate the character.
	bUseControllerRotationYaw = true;

	//Ensures character doesn't rotate based on movement direction.
	GetCharacterMovement()->bOrientRotationToMovement = false;



}

// Called when the game starts or when spawned
void AChara::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerHUD != nullptr)
	{
		UUserWidget* HUD = CreateWidget<UUserWidget>(Cast<APlayerController>(GetController()), PlayerHUD);
		HUD->AddToViewport(9999);
	}

	for (const TSubclassOf<AGun>& GunClass : DefaultWeapons)
	{
		if (!GunClass) continue;

		FActorSpawnParameters Params;
		Params.Owner = this;
		AGun* SpawnedWeapon = GetWorld()->SpawnActor<AGun>(GunClass, Params);

		const int index = Weapons.Add(SpawnedWeapon);

		if (index == CurrentIndex)
		{
			CurrentWeapon = SpawnedWeapon;
			
			if (!CurrentWeapon->CurrentOwner)
			{
				const FTransform& WeaponSlotTransform = CurrentWeapon->PlacementTransform * GetMesh()->GetSocketTransform(FName("ik_hand_gun"));
				CurrentWeapon->SetActorTransform(WeaponSlotTransform, false, nullptr, ETeleportType::TeleportPhysics);
				CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, FName("ik_hand_gun"));

				CurrentWeapon->WeaponMesh->SetVisibility(true);
				CurrentWeapon->CurrentOwner = this;
			}
		}

	}
}

// Called every frame
void AChara::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateStamina();

	TotalAmmo = CurrentWeapon->CurrentAmmoCount;

	CurrentAmmo = CurrentWeapon->CurrentBulletCount;

}

// Called to bind functionality to input
void AChara::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Add input mapping context
	if (APlayerController* PController = Cast<APlayerController>(Controller))
	{
		//Get local player subsystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PController->GetLocalPlayer()))
		{
			//Add input context
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(CharaMove, ETriggerEvent::Triggered, this, &AChara::MoveChara);

		Input->BindAction(CharaLook, ETriggerEvent::Triggered, this, &AChara::LookChara);

		Input->BindAction(CharaJump, ETriggerEvent::Triggered, this, &AChara::JumpChara);

		Input->BindAction(CharaSprint, ETriggerEvent::Triggered, this, &AChara::StartSprint);

		Input->BindAction(CharaSprint, ETriggerEvent::Completed, this, &AChara::EndSprint);

		Input->BindAction(CharaShoot, ETriggerEvent::Completed, this, &AChara::ShootWeapon);

		Input->BindAction(CharaReload, ETriggerEvent::Completed, this, &AChara::ReloadWeapon);

	}
}

void AChara::MoveChara(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if (IsValid(Controller))
	{
		//Get forward direction
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		//Add movement
		AddMovementInput(ForwardDir, InputVector.Y);
		AddMovementInput(RightDir, InputVector.X);
	}
}

void AChara::LookChara(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if (IsValid(Controller))
	{
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(InputVector.Y);
	}
}

void AChara::JumpChara()
{
	AChara::Jump();
}

void AChara::StartSprint()
{
	if (bHasStamina)
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;

		if (GetVelocity().Size() >= 0.5)
		{
			bIsRunning = true;
		}
		else
		{
			bIsRunning = false;
		}
	}
}

void AChara::EndSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	bIsRunning = false;
}

void AChara::UpdateStamina()
{
	//Drain Stamina
	if (bIsRunning)
	{
		CurrentStamina -= StaminaDrainTime;
		CurrentRefillDelayTime = DelayBeforeRefill;
	}

	if (!bIsRunning && CurrentStamina < MaxStamina)
	{
		CurrentRefillDelayTime--;

		if (CurrentRefillDelayTime <= 0)
		{
			CurrentStamina += StaminaRefillTime;
		}
	}

	if (CurrentStamina <= 0)
	{
		bHasStamina = false;
		EndSprint();
	}
	else
	{
		bHasStamina = true;
	}
}

void AChara::ShootWeapon()
{
	if (m_pShootMontage != NULL)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(m_pShootMontage, 1.0f);
		}
	}


	//Adding some info for raytracing.
	const FVector StartTrace = Cam->GetComponentLocation();

	float Range = CurrentWeapon->WeaponRange;

	const FVector EndTrace = (Cam->GetForwardVector() * Range) + StartTrace;

	CurrentWeapon->Shoot(StartTrace, EndTrace);

}

void AChara::ReloadWeapon()
{
	//Add reference to gun class and call the corresponding function
	CurrentWeapon->Reload();
}

void AChara::AimWeapon()
{
	//Add reference to gun class and call the corresponding function

}




