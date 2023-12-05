// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UprisingBunker/AI/UB_AICharacterBase.h"
#include "NeedsComponent.generated.h"

UENUM(BlueprintType)
enum class ENeeds : uint8
{
	EN_Bladder		UMETA(DisplayName = "Bladder"),
	EN_Comfort		UMETA(DisplayName = "Comfort"),
	EN_Energy		UMETA(DisplayName = "Energy"),
	EN_Environment	UMETA(DisplayName = "Environment"),
	EN_Hunger		UMETA(DisplayName = "Hunger"),
	EN_Hygiene		UMETA(DisplayName = "Hygiene"),
	EN_Safety		UMETA(DisplayName = "Safety"),
	EN_Thirst		UMETA(DisplayName = "Thirst")
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

	// List of needs for easy sorting into a list 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Structs|Needs")
	ENeeds CharacterNeeds;

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
