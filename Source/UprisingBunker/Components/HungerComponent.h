// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "NeedsComponent.h"
#include "HungerComponent.generated.h"

USTRUCT(BlueprintType) struct FNeedsHunger
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Hunger")
	FText HungerText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Hunger")
	float MaxHunger;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Needs|Hunger")
	float CurrentHunger;

	// Hunger drain per second when this character is not doing anything else
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Hunger")
	float HungerDrainNormal;

	// Hunger drain per second when this character is working
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Hunger")
	float HungerDrainWorking;

	// Hunger drain per second when this character is sleeping
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Hunger")
	float HungerDrainSleeping;

	// Value at which the character will go and try to fix the problem
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Hunger", meta = (ClampMin = 1.f))
	float HungerFixValue;

	// Default Values
	FNeedsHunger()
	{
		HungerText = FText::FromString("Hunger");
		MaxHunger = 100.f;
		CurrentHunger = MaxHunger;
		HungerDrainNormal = 0.01f;
		HungerDrainWorking = 0.025f;
		HungerDrainSleeping = 0.005f;
		HungerFixValue = 20.f;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPRISINGBUNKER_API UHungerComponent : public UNeedsComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHungerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Structs|Needs")
	FNeedsHunger HungerNeeds;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Getters
	FText GetHungerText() const { return HungerNeeds.HungerText; }
	float GetCurrentHunger() const { return HungerNeeds.CurrentHunger; }

	// Setters
	void AlterHunger(const float AlterAmount);
};
