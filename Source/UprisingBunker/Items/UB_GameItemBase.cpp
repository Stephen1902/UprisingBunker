// Copyright 2023 DME Games


#include "UB_GameItemBase.h"
#include "Components/BoxComponent.h"

// Sets default values
AUB_GameItemBase::AUB_GameItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Root Comp"));
	SetRootComponent(RootComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	MeshComp->SetupAttachment(RootComp);

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
		if (bAllowMultipleChars)
		{
			for (auto& IC : InteractingChars)
			{
				IC.Value += DeltaTime;
				for (const auto& IT : ObjectNeeds)
				{
					if (IT.TimeToAmend <= IC.Value)
					{
								
					}
				}
			}
		}
		else
		{
			
		}
	}
}

void AUB_GameItemBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check what is being overlapped is an AI character
	if (AUB_AICharacterBase* OverlappingChar = Cast<AUB_AICharacterBase>(OtherActor))
	{
		if (bAllowMultipleChars)
		{
			InteractingChars.Add(OverlappingChar, 0.0);
		}
		else
		{
			
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

