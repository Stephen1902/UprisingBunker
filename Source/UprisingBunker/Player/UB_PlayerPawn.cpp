// Copyright 2023 DME Games


#include "UB_PlayerPawn.h"

// Sets default values
AUB_PlayerPawn::AUB_PlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUB_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUB_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUB_PlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

