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

	// ...
}

void UBladderComponent::AlterCurrentBladder(const float BladderIn)
{
	BladderNeeds.CurrentBladder += FMath::Clamp(BladderNeeds.CurrentBladder, 0.f, BladderNeeds.MaxBladder);


}

