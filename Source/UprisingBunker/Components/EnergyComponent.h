// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "NeedsComponent.h"
#include "EnergyComponent.generated.h"

USTRUCT(BlueprintType) struct FNeedsEnergy
{
	GENERATED_BODY();

	// The text to be displayed on the character's widget
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Energy")
	FText EnergyText;

	// Default maximum energy for this character
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Energy")
	float MaxEnergy;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Needs|Energy")
	float CurrentEnergy;

	// Amount per second the energy drops when this character is awake
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Energy")
	float EnergyDrainNormal;

	// Amount per second the energy drops when this character is working
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Energy")
	float EnergyDrainWorking;

	// The amount energy recovers while sleeping.  To be multiplied by the sleep value of the sleeping location.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Energy")
	float EnergyRecoverySleeping;

	// The amount of energy this character has before they will go and try to fix the problem themselves
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Energy", meta = (ClampMin = 1.f))
	float EnergyFixValue;

	// Default Variables
	FNeedsEnergy()
	{
		EnergyText = FText::FromString("Energy");
		MaxEnergy = 100.f;
		CurrentEnergy = MaxEnergy;
		EnergyDrainNormal = 0.01f;
		EnergyDrainWorking = 0.025f;
		EnergyRecoverySleeping = 0.008f;
		EnergyFixValue = 20.f;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPRISINGBUNKER_API UEnergyComponent : public UNeedsComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnergyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Structs|Needs")
	FNeedsEnergy EnergyNeeds;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Getters
	FText GetEnergyText() const { return EnergyNeeds.EnergyText; }
	float GetCurrentEnergy() const { return EnergyNeeds.CurrentEnergy; }

	// Setters
	void AlterEnergy(const float AlterAmount);
		
};
