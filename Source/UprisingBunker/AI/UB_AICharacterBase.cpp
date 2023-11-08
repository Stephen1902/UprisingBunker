// Copyright 2023 DME Games


#include "UB_AICharacterBase.h"
#include "UprisingBunker/Components/EnergyComponent.h"
#include "UprisingBunker/Components/BladderComponent.h"
#include "UprisingBunker/Components/ComfortComponent.h"
#include "UprisingBunker/Components/EnvironmentComponent.h"
#include "UprisingBunker/Components/HygieneComponent.h"
#include "UprisingBunker/Components/SafetyComponent.h"
#include "UprisingBunker/Components/HungerComponent.h"
#include "UprisingBunker/Components/ThirstComponent.h"

// Sets default values
AUB_AICharacterBase::AUB_AICharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnergyComponent = CreateDefaultSubobject<UEnergyComponent>(TEXT("Energy Component"));
	HungerComponent = CreateDefaultSubobject<UHungerComponent>(TEXT("Hunger Component"));
	ThirstComponent = CreateDefaultSubobject<UThirstComponent>(TEXT("Thirst Component"));
	BladderComponent = CreateDefaultSubobject<UBladderComponent>(TEXT("Bladder Component"));
	HygieneComponent = CreateDefaultSubobject<UHygieneComponent>(TEXT("Hygiene Component"));
	ComfortComponent = CreateDefaultSubobject<UComfortComponent>(TEXT("Comfort Component"));
	SafetyComponent = CreateDefaultSubobject<USafetyComponent>(TEXT("Safety Component"));
	EnvironmentComponent = CreateDefaultSubobject<UEnvironmentComponent>(TEXT("Environment Component"));

}

// Called when the game starts or when spawned
void AUB_AICharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUB_AICharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUB_AICharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AUB_AICharacterBase::SetCurrentStatus(const ECharacterStatus NewStatusIn)
{
	CharacterStatus = NewStatusIn;
	OnStatusChanged.Broadcast(CharacterStatus);
}

void AUB_AICharacterBase::RoomEntered(FText RoomName, FText RoomDescription, float Safety, float Environment, float Health, bool CharWorksHere)
{
	OnRoomEntered.Broadcast(Safety, Environment, Health);
}

void AUB_AICharacterBase::RoomExited()
{
	OnRoomEntered.Broadcast(0.f, 0.f, 0.f);
}

