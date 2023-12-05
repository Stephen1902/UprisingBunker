// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UprisingBunker/Components/NeedsComponent.h"
#include "UB_GameItemBase.generated.h"

USTRUCT(BlueprintType)
struct FObjectNeeds
{
	GENERATED_BODY()

	// The need being amended by this actor
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Object Needs")
	ENeeds NeedToAmend;

	// The maximum value this actor can amend
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Object Needs")
	float AmountToAmend;

	// The time taken to amend when a character is interacting with it
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Object Needs")
	float TimeToAmend;

	// Whether this item is to be destroyed when it is used ie a food object
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Object Needs")
	bool bDestroyOnUse;
};

UCLASS()
class UPRISINGBUNKER_API AUB_GameItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUB_GameItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Object Needs")
	TArray<FObjectNeeds> ObjectNeeds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items")
	class UBoxComponent* RootComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items")
	UStaticMeshComponent* MeshComp;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION( )
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


private:
	// The characters currently interacting with this actor and the time they have been interacting
	UPROPERTY()
	TMap<class AUB_AICharacterBase*, float> InteractingChars;

	// Whether or not this actor can be interacted with by more than one character at a time
	bool bAllowMultipleChars;
};
