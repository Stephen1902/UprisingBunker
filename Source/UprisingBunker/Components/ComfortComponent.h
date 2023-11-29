// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "NeedsComponent.h"
#include "ComfortComponent.generated.h"

USTRUCT(BlueprintType) struct FNeedsComfort
{
	GENERATED_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Comfort")
	FText ComfortText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Comfort")
	float MaxComfort;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Needs|Comfort")
	float CurrentComfort;	

	// Comfort drain per second when this character is not doing anything else
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Comfort")
	float ComfortDrainNormal;

	// Comfort drain per second when this character is working
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Comfort")
	float ComfortDrainWorking;

	// Comfort drain per second when this character is sleeping
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Comfort")
	float ComfortDrainSleeping;

	// Comfort recovery per second when resting / sitting / sleeping.  To be multiplied by the value of the furniture.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Comfort")
	float ComfortRecoverySleeping;

	// Value at which the character will go and try to fix the problem
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Comfort", meta = (ClampMin = 1.f))
	float ComfortFixValue;

	// Default Values
	FNeedsComfort()
	{
		ComfortText = FText::FromString("Comfort");
		MaxComfort = 100;
		CurrentComfort = MaxComfort;
		ComfortDrainNormal = 0.001f;
		ComfortDrainWorking = 0.025f;
		ComfortDrainSleeping = 0.005f;
		ComfortRecoverySleeping = 0.002f;
		ComfortFixValue = 20.f;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPRISINGBUNKER_API UComfortComponent : public UNeedsComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComfortComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Structs|Needs")
	FNeedsComfort ComfortNeeds;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Getters
	FText GetComfortText() const { return ComfortNeeds.ComfortText; }
	float GetCurrentComfort() const { return ComfortNeeds.CurrentComfort; }

	// Setters
	void AlterComfort(const float AlterAmount); 
};
