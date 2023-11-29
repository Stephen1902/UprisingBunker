// Copyright 2023 DME Games


#include "HygieneComponent.h"

// Sets default values for this component's properties
UHygieneComponent::UHygieneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHygieneComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHygieneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHygieneComponent::AlterHygiene(const float AlterAmount)
{
	if (!FMath::IsNearlyZero(AlterAmount))
	{
		HygieneNeeds.CurrentHygiene = FMath::Clamp(HygieneNeeds.CurrentHygiene + AlterAmount, 0.f, HygieneNeeds.MaxHygiene);
	}
}

