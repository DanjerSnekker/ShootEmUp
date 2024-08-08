#include "CH_GoWClone/Components/Health.h"


// Sets default values for this component's properties
UHealth::UHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	//-------------------------
	bCanTakeDmg = true;
}


// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealth::Die()
{
	//Add stuff for ragdoll, then timer, followed by Destroy.

	GetOwner()->Destroy();
}

void UHealth::AllowTakeDamage()
{
	bCanTakeDmg = true;
}

void UHealth::TakeDamage(int Damage)
{
	if (bCanTakeDmg) 
	{
		Health -= Damage;
		bCanTakeDmg = false;

		//delay
		FTimerHandle InvincibilityDelay;
		GetWorld()->GetTimerManager().SetTimer(InvincibilityDelay, this, AllowTakeDamage, 0.5f, false);

		//die function
		if (Health <= 0) 
		{
			Die();
		}
	}
}

