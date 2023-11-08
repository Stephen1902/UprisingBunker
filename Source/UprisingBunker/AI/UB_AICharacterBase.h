// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UB_AICharacterBase.generated.h"

UENUM(Blueprintable) 
enum class ECharacterStatus : uint8
{
	ECS_Normal		UMETA(DisplayName = "Normal"),
	ECS_Working		UMETA(DisplayName = "Working"),
	ECS_Resting		UMETA(DisplayName = "Resting"),
	ECS_Consuming	UMETA(DisplayName = "Consuming"),
	ECS_Toilet		UMETA(DisplayName = "Toilet"),
	ECS_Fighting	UMETA(DisplayName = "Fighting"),
	ECS_Mission		UMETA(DisplayName = "On Mission"),
	ECS_Dead		UMETA(DisplayName = "Dead")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatusChanged, ECharacterStatus, NewStatus);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRoomEntered, float, Safety, float, Environment, float, Health);

UCLASS()
class UPRISINGBUNKER_API AUB_AICharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUB_AICharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "Needs")
	class UEnergyComponent* EnergyComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Needs")
	class UHungerComponent* HungerComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Needs")
	class UThirstComponent* ThirstComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Needs")
	class UBladderComponent* BladderComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Needs")
	class UHygieneComponent* HygieneComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Needs")
	class UComfortComponent* ComfortComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Needs")
	class USafetyComponent* SafetyComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Needs")
	class UEnvironmentComponent* EnvironmentComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when the status of this character changes
	UPROPERTY(BlueprintAssignable)
	FOnStatusChanged OnStatusChanged;

	UPROPERTY(BlueprintAssignable)
	FOnRoomEntered OnRoomEntered;

	ECharacterStatus GetCurrentStatus() const { return CharacterStatus;  }
	void SetCurrentStatus(const ECharacterStatus NewStatusIn);

	void RoomEntered(FText RoomName, FText RoomDescription, float Safety, float Environment, float Health, bool CharWorksHere);
	void RoomExited();
private:
	// Current status of this character
	UPROPERTY()
	ECharacterStatus CharacterStatus;
};
