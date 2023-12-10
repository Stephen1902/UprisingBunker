// Copyright 2023 DME Games


#include "BladderComponent.h"
#include "UprisingBunker/AI/UB_AICharacterBase.h"

// Sets default values for this component's properties
UBladderComponent::UBladderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBladderComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBladderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentCharacterStatus != ECharacterStatus::ECS_Dead)
	{
		CalculateTickBladderChange(DeltaTime);
	}
}

void UBladderComponent::AlterBladder(const float AlterAmount)
{
	BladderNeeds.CurrentBladder = FMath::Clamp(BladderNeeds.CurrentBladder + AlterAmount, 0.f, BladderNeeds.MaxBladder);
}

void UBladderComponent::CalculateTickBladderChange(float DeltaTime)
{
	float ChangeThisTick;

	// Get the current bladder drain per second, depending on if the character is sleeping or not
	if (CurrentCharacterTask == ECharacterTask::ECT_Sleeping)
	{
		ChangeThisTick = BladderNeeds.BladderDrainSleeping;
	}
	else
	{
		ChangeThisTick = BladderNeeds.BladderDrainNormal;
	}

	// Check if the character has a high enough water level to trigger a penalty 
	if (CompOwner->GetCurrentThirstLevel() > BladderNeeds.WaterPenaltyThreshold)
	{
		ChangeThisTick *= (1.0f + BladderNeeds.WaterPenaltyMultiplier);
	}

	// Multiply by DeltaTime to keep it frame rate independent
	ChangeThisTick *= DeltaTime;

	// Change the bladder level calculated
	AlterBladder(ChangeThisTick);
}

