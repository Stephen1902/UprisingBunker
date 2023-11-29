// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "NeedsComponent.h"
#include "SafetyComponent.generated.h"

USTRUCT(BlueprintType) struct FNeedsSafety
{
	GENERATED_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Safety")
	FText SafetyText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Safety")
	float MaxSafety;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Needs|Safety")
	float CurrentSafety;

	// Value at which this character will try to fix their safety
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Safety", meta=(ClampMin = 1.f))
	float SafetyFixValue;

	// Default Values
	FNeedsSafety()
	{
		SafetyText = FText::FromString("Safety");
		MaxSafety = 100;
		CurrentSafety = MaxSafety;
		SafetyFixValue = 10.f;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPRISINGBUNKER_API USafetyComponent : public UNeedsComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USafetyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Structs|Needs")
	FNeedsSafety SafetyNeeds;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Getters
	FText GetSafetyText() const { return SafetyNeeds.SafetyText; }
	float GetCurrentSafety() const { return SafetyNeeds.CurrentSafety; }

	// Setters
	void AlterSafety(const float AlterAmount); 
};
