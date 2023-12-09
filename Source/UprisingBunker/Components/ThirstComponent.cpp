// Copyright 2023 DME Games


#include "ThirstComponent.h"

// Sets default values for this component's properties
UThirstComponent::UThirstComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UThirstComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UThirstComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AlterThirstThisTick(DeltaTime);
}

void UThirstComponent::AlterThirst(const float AlterAmount)
{
	if (!FMath::IsNearlyZero(AlterAmount))
	{
		ThirstNeeds.CurrentThirst = FMath::Clamp(ThirstNeeds.CurrentThirst + AlterAmount, 0.f, ThirstNeeds.MaxThirst);

		if (ThirstNeeds.CurrentThirst <= ThirstNeeds.ThirstFixValue)
		{
			
		}
	}
}

void UThirstComponent::AlterThirstThisTick(float DeltaTime)
{
	float ChangeThisTick;

	switch (CurrentCharacterTask)
	{
		case ECharacterTask::ECT_Consuming:
		case ECharacterTask::ECT_Fighting:
		case ECharacterTask::ECT_Mission:
		case ECharacterTask::ECT_Normal:
		case ECharacterTask::ECT_Toilet:
		default:
			ChangeThisTick = ThirstNeeds.ThirstDrainNormal;
		break;
		case ECharacterTask::ECT_Resting:
		case ECharacterTask::ECT_Sleeping:
			ChangeThisTick = ThirstNeeds.ThirstDrainSleeping;
		break;
		case ECharacterTask::ECT_Working:
			ChangeThisTick = ThirstNeeds.ThirstDrainWorking;
		break;
		case ECharacterTask::ECT_Dead:
			ChangeThisTick = 0.f;
		break;
	}

	ChangeThisTick *= DeltaTime;

	AlterThirst(ChangeThisTick);
}

