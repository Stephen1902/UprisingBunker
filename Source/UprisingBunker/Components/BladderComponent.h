// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "NeedsComponent.h"
#include "BladderComponent.generated.h"


USTRUCT(BlueprintType) struct FNeedsBladder
{
	GENERATED_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Bladder")
	FText BladderText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Bladder")
	float MaxBladder;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Needs|Bladder")
	float CurrentBladder;

	// Bladder drain per second when this character is not doing anything else
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Bladder")
	float BladderDrainNormal;

	// Bladder drain per second when this character is sleeping
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Bladder")
	float BladderDrainSleeping;

	// Value at which the character will go and try to fix the problem
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Bladder", meta = (ClampMin = 1.f))
	float BladderFixValue;

	// Penalty for if the character's water level is above a certain threshold
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Bladder")
	float WaterPenaltyThreshold;

	// Multiplier for the water leven penalty
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Bladder", meta=(EditCondition="WaterPenaltyThreshold<100.f"));
	float WaterPenaltyMultiplier;

	// Default Values
	FNeedsBladder()
	{
		BladderText = FText::FromString("Bladder");
		MaxBladder = 100.f;
		CurrentBladder = MaxBladder;
		BladderDrainNormal = 0.01f;
		BladderDrainSleeping = 0.015f;
		BladderFixValue = 20.f;
		WaterPenaltyThreshold = 100.f;
		WaterPenaltyMultiplier = 0.0f;
	}
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPRISINGBUNKER_API UBladderComponent : public UNeedsComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBladderComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Structs|Needs")
	FNeedsBladder BladderNeeds;

	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Getters
	FText GetBladderText() const { return BladderNeeds.BladderText; }
	float GetCurrentBladder() const { return BladderNeeds.CurrentBladder; }

	// Setters
	void AlterCurrentBladder(const float BladderIn);
};
