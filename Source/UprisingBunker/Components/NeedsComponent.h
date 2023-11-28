// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UprisingBunker/AI/UB_AICharacterBase.h"
#include "NeedsComponent.generated.h"

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
class UPRISINGBUNKER_API UNeedsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNeedsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Structs|Needs")
	FNeedsHunger HungerNeeds;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Structs|Needs")
	FNeedsHygiene HygieneNeeds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Structs|Needs")
	FNeedsComfort ComfortNeeds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Structs|Needs")
	FNeedsSafety SafetyNeeds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Structs|Needs")
	FNeedsEnvironment EnvironmentNeeds;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Character that owns this component
	UPROPERTY()
	class AUB_AICharacterBase* CompOwner;

	UFUNCTION()
	void CharacterTaskChanged(ECharacterTask NewTask);
	ECharacterTask CurrentCharacterTask;

	UFUNCTION()
	void CharacterStatusChanged(ECharacterStatus NewStatus);
	ECharacterStatus CurrentCharacterStatus;

	UFUNCTION()
	void CharacterNewRoom(float Safety, float Environment, float Health);
	
	float RoomSafety;
	float RoomEnvironment;
	float RoomHealth;
};
