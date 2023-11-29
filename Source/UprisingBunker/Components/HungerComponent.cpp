// Copyright 2023 DME Games


#include "HungerComponent.h"

// Sets default values for this component's properties
UHungerComponent::UHungerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHungerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHungerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHungerComponent::AlterHunger(const float AlterAmount)
{
	if (!FMath::IsNearlyZero(AlterAmount))
	{
		HungerNeeds.CurrentHunger = FMath::Clamp(HungerNeeds.CurrentHunger + AlterAmount, 0.f, HungerNeeds.MaxHunger);
	}
}

