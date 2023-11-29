// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "NeedsComponent.h"
#include "HygieneComponent.generated.h"

USTRUCT(BlueprintType) struct FNeedsHygiene
{
	GENERATED_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Hygiene")
	FText HygieneText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Hygiene")
	float MaxHygiene;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Needs|Hygiene")
	float CurrentHygiene;
	
	// Hygiene drain per second when this character is not doing anything else
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Hygiene")
	float HygieneDrainNormal;

	// Hygiene drain per second when this character is working
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Hygiene")
	float HygieneDrainWorking;

	// Hygiene drain per second when this character is sleeping
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Hygiene")
	float HygieneDrainSleeping;

	// Value at which the character will go and try to fix the problem
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Hygiene", meta = (ClampMin = 1.f))
	float HygieneFixValue;

	// Default Values
	FNeedsHygiene()
	{
		HygieneText = FText::FromString("Hygiene");
		MaxHygiene = 100.f;
		CurrentHygiene = MaxHygiene;
		HygieneDrainNormal = 0.01f;
		HygieneDrainWorking = 0.033f;
		HygieneDrainSleeping = 0.005f;
		HygieneFixValue = 20.f;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPRISINGBUNKER_API UHygieneComponent : public UNeedsComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHygieneComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Structs|Needs")
	FNeedsHygiene HygieneNeeds;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Getters
	FText GetHygieneText() const { return HygieneNeeds.HygieneText; }
	float GetCurrentHygiene() const { return HygieneNeeds.CurrentHygiene; }

	// Setters
	void AlterHygiene(const float AlterAmount);
}; 
