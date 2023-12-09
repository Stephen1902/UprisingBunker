// Copyright 2023 DME Games

#include "NeedsComponent.h"
#include "UprisingBunker/AI/UB_AICharacterBase.h"

// Sets default values for this component's properties
UNeedsComponent::UNeedsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CompOwner = nullptr;
	CurrentCharacterTask = ECharacterTask::ECT_Normal;
	CurrentCharacterStatus = ECharacterStatus::ECS_Healthy;
	CurrentCharacterNeed = ECharacterNeeds::EN_None;
	RoomSafety = 50.f;
	RoomEnvironment = 50.f;
	RoomHealth = 100.f;
	
}


// Called when the game starts
void UNeedsComponent::BeginPlay()
{
	Super::BeginPlay();

	CompOwner = Cast<AUB_AICharacterBase>(GetOwner());

	if (CompOwner)
	{
		CompOwner->OnTaskChanged.AddDynamic(this, &UNeedsComponent::CharacterTaskChanged);
		CompOwner->OnStatusChanged.AddDynamic(this, &UNeedsComponent::CharacterStatusChanged);
		CompOwner->OnNeedChanged.AddDynamic(this, &UNeedsComponent::CharacterNeedsChanged);
		CompOwner->OnRoomEntered.AddDynamic(this, &UNeedsComponent::CharacterNewRoom);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to get owner on this component"));
	}
}


// Called every frame
void UNeedsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UNeedsComponent::CharacterTaskChanged(ECharacterTask NewTask)
{
	UE_LOG(LogTemp, Warning, TEXT("Task changed"));
	CurrentCharacterTask = NewTask;
}

void UNeedsComponent::CharacterStatusChanged(ECharacterStatus NewStatus)
{
	UE_LOG(LogTemp, Warning, TEXT("Status Changed"));
	CurrentCharacterStatus = NewStatus;
}

void UNeedsComponent::CharacterNeedsChanged(ECharacterNeeds NewNeed)
{
	UE_LOG(LogTemp, Warning, TEXT("Need Changed"));
	CurrentCharacterNeed = NewNeed;
}

void UNeedsComponent::CharacterNewRoom(const float Safety, const float Environment, const float Health)
{
	RoomSafety = Safety;
	RoomEnvironment = Environment;
	RoomHealth = Health;
}
