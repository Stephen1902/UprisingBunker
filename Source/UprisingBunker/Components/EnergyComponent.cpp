// Copyright 2023 DME Games


#include "EnergyComponent.h"
#include "UprisingBunker/AI/UB_AICharacterBase.h"

// Sets default values for this component's properties
UEnergyComponent::UEnergyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnergyComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UEnergyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEnergyComponent::AlterEnergy(const float AlterAmount)
{
	if (!FMath::IsNearlyZero(AlterAmount))
	{
		EnergyNeeds.CurrentEnergy = FMath::Clamp(EnergyNeeds.CurrentEnergy + AlterAmount, 0.f, EnergyNeeds.MaxEnergy);

		// Check that the character isn't already sleeping
		if (CurrentCharacterTask != ECharacterTask::ECT_Sleeping)
		{

		}
		else
		{
			// The character is sleeping, check if their energy has reached maximum level
			if (EnergyNeeds.CurrentEnergy == EnergyNeeds.MaxEnergy)
			{
				// Energy is full, wake the character
				CompOwner->SetCurrentTask(ECharacterTask::ECT_Normal);

				// TODO random waking rather than the instant energy is full
			}
		}
	}
}
