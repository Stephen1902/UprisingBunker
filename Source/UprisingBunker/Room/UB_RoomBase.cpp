// Copyright 2023 DME Games


#include "UB_RoomBase.h"
#include "UprisingBunker/AI/UB_AICharacterBase.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"

// Sets default values
AUB_RoomBase::AUB_RoomBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Root Comp"));
	SetRootComponent(RootComp);
	RootComp->SetBoxExtent(FVector(256.f));

	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	BaseMeshComp->SetupAttachment(RootComp);

	BaseLightComp = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light Comp"));
	BaseLightComp->SetupAttachment(BaseMeshComp);

	RoomStatusCurrent.SafetyBase = 50.f;
	RoomStatusCurrent.SafetyMax = 100.f;
	RoomStatusCurrent.EnvironmentBase = 50.f;
	RoomStatusCurrent.EnvironmentMax = 100.f;
	RoomStatusCurrent.HealthBase = 100.f;
	RoomStatusCurrent.HealthMax = 100.f;
	RoomStatusCurrent.HealthDropPerSecond = 0.f;
	SafetyCurrent = 0.f;
	EnvironmentCurrent = 0.f;
	HealthCurrent = 0.f;	
}

#if WITH_EDITOR
void AUB_RoomBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if what has overlapped with this component is an AI Character
	if (AUB_AICharacterBase* OverlappedIsChar = Cast<AUB_AICharacterBase>(OtherActor))
	{
		// Add it to the database
		OverlappingActors.AddUnique(OverlappedIsChar);
		const bool bOverlappingWorksHere = AIWorksHere.Contains(OverlappedIsChar);
		OverlappedIsChar->RoomEntered(RoomName, RoomDescription, SafetyCurrent, EnvironmentCurrent, HealthCurrent, bOverlappingWorksHere);
	}
}

void AUB_RoomBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Check if what has exited the overlap is an AI Character
	if (AUB_AICharacterBase* OverlappedIsChar = Cast<AUB_AICharacterBase>(OtherActor))
	{
		// Remove it from the database
		OverlappingActors.RemoveSingle(OverlappedIsChar);
	}
}

void AUB_RoomBase::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (RoomStatusCurrent.SafetyBase > SafetyCurrent) { SafetyCurrent = RoomStatusCurrent.SafetyBase; }
	if (RoomStatusCurrent.SafetyBase > RoomStatusCurrent.SafetyMax) { RoomStatusCurrent.SafetyMax = RoomStatusCurrent.SafetyBase; }

	if (RoomStatusCurrent.EnvironmentBase > EnvironmentCurrent) { EnvironmentCurrent = RoomStatusCurrent.EnvironmentBase; }
	if (RoomStatusCurrent.EnvironmentBase > RoomStatusCurrent.EnvironmentMax) { RoomStatusCurrent.EnvironmentMax = RoomStatusCurrent.EnvironmentBase; }
}
#endif

// Called when the game starts or when spawned
void AUB_RoomBase::BeginPlay()
{
	Super::BeginPlay();

	RootComp->OnComponentBeginOverlap.AddDynamic(this, &AUB_RoomBase::OnBeginOverlap);
	RootComp->OnComponentEndOverlap.AddDynamic(this, &AUB_RoomBase::OnEndOverlap);
}

// Called every frame
void AUB_RoomBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (RoomStatusCurrent.HealthDropPerSecond > 0.f)
	{
		AlterHealth(-RoomStatusCurrent.HealthDropPerSecond * DeltaTime);
	}

}

void AUB_RoomBase::AlterSafety(float AmountToAdjust)
{
	if (AmountToAdjust != 0.f)
	{
		SafetyCurrent += FMath::Clamp(SafetyCurrent, 0.f, RoomStatusCurrent.SafetyMax);
	}
}

float AUB_RoomBase::GetSafetyAsPercentage()
{
	return 1.0f - ((RoomStatusCurrent.SafetyMax - SafetyCurrent) / RoomStatusCurrent.SafetyMax);
}

void AUB_RoomBase::AlterEnvironment(float AmountToAdjust)
{
	if (AmountToAdjust != 0.f)
	{
		EnvironmentCurrent += FMath::Clamp(EnvironmentCurrent, 0.f, RoomStatusCurrent.EnvironmentMax);
	}
}

float AUB_RoomBase::GetEnvironmentAsPercentage()
{
	return 1.0f - ((RoomStatusCurrent.EnvironmentMax - EnvironmentCurrent) / RoomStatusCurrent.EnvironmentMax);
}

void AUB_RoomBase::AlterHealth(float AmountToAdjust)
{
	if (AmountToAdjust != 0.f)
	{
		HealthCurrent += FMath::Clamp(HealthCurrent, 0.f, RoomStatusCurrent.HealthMax);
	}
}

float AUB_RoomBase::GetHealthAsPercentage()
{
	return 1.0f - ((RoomStatusCurrent.HealthMax - HealthCurrent) / RoomStatusCurrent.HealthMax);
}

void AUB_RoomBase::ChangeRoomStatus(const ERoomStatus NewRoomStatus)
{
	// Get the new room status from the array
	for (const auto& RS : RoomStatusArray)
	{
		// If found, update variables to match
		if (RS.RoomStatus == NewRoomStatus)
		{
			RoomStatusCurrent.RoomStatus = NewRoomStatus;
			RoomStatusCurrent.EnvironmentBase = RS.EnvironmentBase;
			RoomStatusCurrent.EnvironmentMax = RS.EnvironmentMax;
			RoomStatusCurrent.HealthBase = RS.HealthBase;
			RoomStatusCurrent.HealthMax = RS.HealthMax;
			RoomStatusCurrent.SafetyBase = RS.SafetyBase;
			RoomStatusCurrent.SafetyMax = RS.SafetyMax;
			RoomStatusCurrent.HealthDropPerSecond = RS.HealthDropPerSecond;
		}
	}
}
