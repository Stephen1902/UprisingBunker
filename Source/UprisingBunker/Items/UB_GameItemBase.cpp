// Copyright 2023 DME Games


#include "UB_GameItemBase.h"
#include "Components/BoxComponent.h"
#include "UprisingBunker/AI/UB_AICharacterBase.h"

// Sets default values
AUB_GameItemBase::AUB_GameItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set this actor to only tick 20 times a second.  It will be casting on tick
	PrimaryActorTick.TickInterval = 0.05f;

	RootComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Root Comp"));
	SetRootComponent(RootComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	MeshComp->SetupAttachment(RootComp);

	ItemName = FText::FromString("Default Name");
	ItemDescription = FText::FromString("Default Description");
	ItemCost = 20.f;
	bAllowMultipleChars = false;
}

// Called when the game starts or when spawned
void AUB_GameItemBase::BeginPlay()
{
	Super::BeginPlay();

	RootComp->OnComponentBeginOverlap.AddDynamic(this, &AUB_GameItemBase::OnBeginOverlap);
	RootComp->OnComponentEndOverlap.AddDynamic(this, &AUB_GameItemBase::OnEndOverlap);
	
}

// Called every frame
void AUB_GameItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InteractingChars.Num() > 0)
	{
		for (auto& InteractingChar : InteractingChars)
		{
			// Add the delta time to the current interacting time of this character
			InteractingChar.Value += DeltaTime;
			// Iterate through the needs that this item affects
			for (const auto& ObjectNeed : ObjectNeeds)
			{
				// Check if the time it takes for this object to complete is less than the time the character has been interacting
				if (ObjectNeed.TimeToAmend <= InteractingChar.Value)
				{
					InteractingChar.Key->AmendCharacterNeed(ObjectNeed.NeedToAmend, ObjectNeed.AmountToAmend * DeltaTime);
				}
				else
				{
					InteractingChar.Key->ItemNeedHasFinished(ObjectNeed.NeedToAmend);
				}
			}
		}
	}
}

void AUB_GameItemBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check what is being overlapped is an AI character
	if (AUB_AICharacterBase* OverlappingChar = Cast<AUB_AICharacterBase>(OtherActor))
	{
		InteractingChar = OverlappingChar;
		if (bAllowMultipleChars || InteractingChars.Num() == 0)
		{
			InteractingChars.Add(OverlappingChar, 0.0);
		}
	}
}

void AUB_GameItemBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (const AUB_AICharacterBase* OverlappingChar = Cast<AUB_AICharacterBase>(OtherActor))
	{
		InteractingChars.Remove(OverlappingChar);
	}
}

