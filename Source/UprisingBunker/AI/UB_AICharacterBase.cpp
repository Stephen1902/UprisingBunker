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

	CurrentHealth = CharacterInfo.CharacterMaxHealth;
	
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

void AUB_AICharacterBase::SetCurrentTask(const ECharacterTask NewTaskIn)
{
	CharacterTask = NewTaskIn;
	OnTaskChanged.Broadcast(CharacterTask);
}

void AUB_AICharacterBase::SetCurrentStatus(const ECharacterStatus NewStatusIn)
{
	CharacterStatus = NewStatusIn;
	OnStatusChanged.Broadcast(CharacterStatus);
}

void AUB_AICharacterBase::SetCurrentNeed(const ECharacterNeeds NewNeedIn)
{
	CharacterNeeds = NewNeedIn;
	OnNeedChanged.Broadcast(CharacterNeeds);
}

void AUB_AICharacterBase::RoomEntered(FText RoomName, FText RoomDescription, float Safety, float Environment, float Health, bool CharWorksHere)
{
	OnRoomEntered.Broadcast(Safety, Environment, Health);
}

void AUB_AICharacterBase::RoomExited()
{
	OnRoomEntered.Broadcast(0.f, 0.f, 0.f);
}

float AUB_AICharacterBase::GetCurrentBladderLevel() const
{
	return BladderComponent->GetCurrentBladder();
}

float AUB_AICharacterBase::GetCurrentComfortLevel() const
{
	return ComfortComponent->GetCurrentComfort();
}

float AUB_AICharacterBase::GetCurrentEnergyLevel() const
{
	return EnergyComponent->GetCurrentEnergy();
}

float AUB_AICharacterBase::GetCurrentEnvironmentLevel() const
{
	return EnvironmentComponent->GetCurrentEnvironment();
}

float AUB_AICharacterBase::GetCurrentHungerLevel() const
{
	return HungerComponent->GetCurrentHunger();
}

float AUB_AICharacterBase::GetCurrentHygieneLevel() const
{
	return HygieneComponent->GetCurrentHygiene();
}

float AUB_AICharacterBase::GetCurrentSafetyLevel() const
{
	return SafetyComponent->GetCurrentSafety();
}

float AUB_AICharacterBase::GetCurrentThirstLevel() const
{
	return ThirstComponent->GetCurrentThirst();
}

void AUB_AICharacterBase::AmendCharacterNeed(const ECharacterNeeds NeedToAmend, const float Value) const
{
	if (NeedToAmend != ECharacterNeeds::EN_None && Value > 0.f)
	{
		switch (NeedToAmend)
		{
		case NeedToAmend == ECharacterNeeds::EN_Bladder:
			BladderComponent->AlterBladder(Value);
			break;
		case NeedToAmend == ECharacterNeeds::EN_Comfort:
			ComfortComponent->AlterComfort(Value);
			break;
		case NeedToAmend == ECharacterNeeds::EN_Energy:
			EnergyComponent->AlterEnergy(Value);
			break;
		case NeedToAmend == ECharacterNeeds::EN_Environment:
			EnvironmentComponent->AlterEnvironment(Value);
			break;
		case NeedToAmend == ECharacterNeeds::EN_Hunger:
			HungerComponent->AlterHunger(Value);
			break;
		case NeedToAmend == ECharacterNeeds::EN_Hygiene:
			HygieneComponent->AlterHygiene(Value);
			break;
		case NeedToAmend == ECharacterNeeds::EN_Safety:
			SafetyComponent->AlterSafety(Value);
			break;
		case NeedToAmend == ECharacterNeeds::EN_Thirst:
			ThirstComponent->AlterThirst(Value);
			break;
		case NeedToAmend == ECharacterNeeds::EN_None:
		default:
			break;
		}
	}
}

void AUB_AICharacterBase::ItemNeedHasFinished(const ECharacterNeeds NeedToAmend)
{
}
