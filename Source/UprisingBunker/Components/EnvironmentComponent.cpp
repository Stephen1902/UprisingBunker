// Copyright 2023 DME Games


#include "EnvironmentComponent.h"

// Sets default values for this component's properties
UEnvironmentComponent::UEnvironmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnvironmentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEnvironmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEnvironmentComponent::AlterEnvironment(const float AlterAmount)
{
	if (!FMath::IsNearlyZero(AlterAmount))
	{
		EnvironmentNeeds.CurrentEnvironment = FMath::Clamp(EnvironmentNeeds.CurrentEnvironment + AlterAmount, 0.f, EnvironmentNeeds.MaxEnvironment);
	}
}

