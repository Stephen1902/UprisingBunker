// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UB_AICharacterBase.generated.h"

UENUM(Blueprintable) 
enum class ECharacterTask : uint8
{
	ECT_Normal		UMETA(DisplayName = "Normal"),
	ECT_Working		UMETA(DisplayName = "Working"),
	ECT_Resting		UMETA(DisplayName = "Resting"),
	ECT_Sleeping	UMETA(DisplayName = "Sleeping"),
	ECT_Consuming	UMETA(DisplayName = "Consuming"),
	ECT_Toilet		UMETA(DisplayName = "Toilet"),
	ECT_Fighting	UMETA(DisplayName = "Fighting"),
	ECT_Mission		UMETA(DisplayName = "On Mission"),
	ECT_Dead		UMETA(DisplayName = "Dead")
};

UENUM(Blueprintable)
enum class ECharacterStatus : uint8
{
	ECS_Healthy		UMETA(DisplayName = "Healthy"),
	ECS_Injured		UMETA(DisplayName = "Injured"),
	ECS_Sick		UMETA(DisplayName = "Sick"),
	ECS_Dying		UMETA(DisplayName = "Dying"),
	ECS_Dead		UMETA(DisplayName = "Dead")
};

UENUM(Blueprintable)
enum class ECharacterMood : uint8
{
	ECM_VMotivated		UMETA(DisplayName = "Very Motivated"),
	ECM_Motivated		UMETA(DisplayName = "Motivated"),
	ECM_Neither			UMETA(DisplayName = "Neither Motivated Nor Demotivated"),
	ECM_Unmotivated		UMETA(DisplayName = "Unmotivated"),
	ECM_VUnmotivated	UMETA(DisplayName = "Very Unmotivated")
};

UENUM(Blueprintable)
enum class ECharacterGender : uint8
{
	ECG_Male	UMETA(DisplayName = "Male"),
	ECG_Female	UMETA(DisplayName = "Female")
};


UENUM(Blueprintable)
enum class EMaritalStatus : uint8
{
	EMS_Single		UMETA(DisplayName = "Single"),
	EMS_Engaged		UMETA(DisplayName = "Engaged"),
	EMS_Married		UMETA(DisplayName = "Married"),
	EMS_Divorced	UMETA(DisplayName = "Divorced"),
	EMS_Widowed		UMETA(DisplayName = "Widowed")
};

USTRUCT(BlueprintType)
struct FCharacterInfo
{
	GENERATED_BODY();

	// Surname of this character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Set Up")
	FText Forename;

	// First name of this character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Set Up")
	FText Surname;

	// Gender of this character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Set Up")
	ECharacterGender Gender;	

	// Date of birth for this character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Set Up")
	FDateTime DOB;

	// Marital status of this character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Set Up")
	EMaritalStatus MaritalStatus;

	// Mood of this character when they are created
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Set Up")
	ECharacterMood CharacterMood;
	
	FCharacterInfo()
	{
		Forename = FText::FromString("John");
		Surname = FText::FromString("Doe");
		Gender = ECharacterGender::ECG_Male;
		DOB = FDateTime(1976, 12, 5);
		MaritalStatus = EMaritalStatus::EMS_Single;
		CharacterMood = ECharacterMood::ECM_Neither;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTaskChanged, ECharacterTask, NewTask);
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

	// Called when the task of this character changes
	UPROPERTY(BlueprintAssignable)
	FOnTaskChanged OnTaskChanged;

	UPROPERTY(BlueprintAssignable)
	FOnStatusChanged OnStatusChanged;
	
	// Called when the character enters a new room
	UPROPERTY(BlueprintAssignable)
	FOnRoomEntered OnRoomEntered;

	ECharacterTask GetCurrentTask() const { return CharacterTask;  }
	void SetCurrentTask(const ECharacterTask NewTaskIn);

	ECharacterStatus GetCurrentStatus() const { return CharacterStatus; }
	void SetCurrentStatus(const ECharacterStatus NewStatusIn);

	void RoomEntered(FText RoomName, FText RoomDescription, float Safety, float Environment, float Health, bool CharWorksHere);
	void RoomExited();
	
	ECharacterStatus GetCharacterStatus() const { return CharacterStatus; }

	float GetCurrentThirstLevel() const;
private:
	// Current task of this character
	UPROPERTY()
	ECharacterTask CharacterTask;

	// Current status of this character
	UPROPERTY()
	ECharacterStatus CharacterStatus;
};
