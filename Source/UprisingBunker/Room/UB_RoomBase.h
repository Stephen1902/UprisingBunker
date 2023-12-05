// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UB_RoomBase.generated.h"

UENUM(BlueprintType)
enum class ERoomStatus : uint8
{
	ERS_Normal		UMETA(DisplayName="Normal"),
	ERS_NoWorkers	UMETA(DisplayNane="No Workers"),
	ERS_NoPower		UMETA(DisplayName="No Power"),
	ERS_Attack		UMETA(DisplayName="Under Attack"),
	ERS_Damaged		UMETA(DisplayName="Damaged")
};

USTRUCT(BlueprintType)
struct FRoomStatus
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Status")
	ERoomStatus RoomStatus;

	// The base safety rating of this room when spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Status")
	float SafetyBase;

	// The maximum safety rating of this room
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Status")
	float SafetyMax;

	// The base environment rating of this room when spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Status")
	float EnvironmentBase;

	// The maximum environment rating for this room
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Status")
	float EnvironmentMax;

	// The base health level of this room when spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Status")
	float HealthBase;

	// The maximum health level of this room
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Status")
	float HealthMax;

	// Room health degradation per second
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Status")
	float HealthDropPerSecond;
};

UCLASS()
class UPRISINGBUNKER_API AUB_RoomBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUB_RoomBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Collision component for this room 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rooms")
	class UBoxComponent* RootComp;

	// Basic mesh for the room
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rooms")
	UStaticMeshComponent* BaseMeshComp;

	// Basic light for the room
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rooms")
	class UPointLightComponent* BaseLightComp;
	
	// The name of this room as displayed on screen
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rooms")
	FText RoomName;

	// The description of this room, as displayed on screen
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rooms")
	FText RoomDescription;

	// Set parameters for the room in its various statuses
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rooms")
	TArray<FRoomStatus> RoomStatusArray;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Rooms")
	void AlterSafety(float AmountToAdjust);

	// Get the current room safety, based on a maximum of the maximum
	UFUNCTION(BlueprintCallable, Category = "Rooms")
	float GetSafetyAsPercentage();

	UFUNCTION(BlueprintCallable, Category = "Rooms")
	void AlterEnvironment(float AmountToAdjust);

	UFUNCTION(BlueprintCallable, Category = "Rooms")
	float GetEnvironmentAsPercentage();

	UFUNCTION(BlueprintCallable, Category = "Rooms")
	void AlterHealth(float AmountToAdjust);

	// Get the current room Health, based on a maximum of the maximum
	UFUNCTION(BlueprintCallable, Category = "Rooms")
	float GetHealthAsPercentage();

	UFUNCTION(BlueprintCallable, Category="Rooms")
	ERoomStatus GetRoomStatus() const { return RoomStatusEnum; }

	UFUNCTION(BlueprintCallable, Category="Rooms")
	void ChangeRoomStatus(const ERoomStatus NewRoomStatus );
private:
	float SafetyCurrent;
	float EnvironmentCurrent;
	float HealthCurrent;

	UFUNCTION( )
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	// All AI Characters currently overlapping this actor
	TArray<class AUB_AICharacterBase*> OverlappingActors;

	// AI Characters that "work" in this room
	TArray<AUB_AICharacterBase*> AIWorksHere;

	UPROPERTY()
	ERoomStatus RoomStatusEnum;

	UPROPERTY()
	FRoomStatus RoomStatusStruct;
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
