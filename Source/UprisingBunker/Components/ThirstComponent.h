// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "NeedsComponent.h"
#include "ThirstComponent.generated.h"

USTRUCT(BlueprintType) struct FNeedsThirst
{
	GENERATED_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Thirst")
	FText ThirstText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Thirst")
	float MaxThirst;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Needs|Thirst")
	float CurrentThirst;

	// Thirst drain per second when this character is not doing anything else
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Thirst")
	float ThirstDrainNormal;

	// Thirst drain per second when this character is working
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Thirst")
	float ThirstDrainWorking;

	// Thirst drain per second when this character is sleeping
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Thirst")
	float ThirstDrainSleeping;

	// Value at which the character will go and try to fix the problem
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Thirst", meta = (ClampMin = 1.f))
	float ThirstFixValue;

	// Default Values
	FNeedsThirst()
	{
		ThirstText = FText::FromString("Thirst");
		MaxThirst = 100.f;
		CurrentThirst = MaxThirst;
		ThirstDrainNormal = 0.01f;
		ThirstDrainWorking = 0.025f;
		ThirstDrainSleeping = 0.005f;
		ThirstFixValue = 20.f;
	}

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPRISINGBUNKER_API UThirstComponent : public UNeedsComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UThirstComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Structs|Needs")
	FNeedsThirst ThirstNeeds;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Getters
	FText GetThirstText() const { return ThirstNeeds.ThirstText; }
	float GetThirstLevel() const { return ThirstNeeds.CurrentThirst; }

	// Setters
	void AlterThirst(const float AlterAmount);
};
