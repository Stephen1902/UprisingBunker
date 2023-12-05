// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "NeedsComponent.h"
#include "EnvironmentComponent.generated.h"

USTRUCT(BlueprintType) struct FNeedsEnvironment
{
	GENERATED_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Environment")
	FText EnvironmentText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Environment")
	float MaxEnvironment;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Needs|Environment")
	float CurrentEnvironment;

	// Value at which this character will try to fix their environment
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Needs|Environment", meta=(ClampMin = 1.f))
	float EnvironmentFixValue;

	// Defaults
	FNeedsEnvironment()
	{
		EnvironmentText = FText::FromString("Environment");
		MaxEnvironment = 100;
		CurrentEnvironment = MaxEnvironment;
		EnvironmentFixValue = 10.f;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPRISINGBUNKER_API UEnvironmentComponent : public UNeedsComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnvironmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Structs|Needs")
	FNeedsEnvironment EnvironmentNeeds;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Getters
	FText GetEnvironmentText() const { return EnvironmentNeeds.EnvironmentText; }
	float GetCurrentEnvironment() const { return EnvironmentNeeds.CurrentEnvironment; }

	// Setters
	void AlterEnvironment(const float AlterAmount);
};
