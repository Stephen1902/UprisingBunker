// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UprisingBunker/AI/UB_AICharacterBase.h"
#include "NeedsComponent.generated.h"

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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Character that owns this component
	UPROPERTY()
	AUB_AICharacterBase* CompOwner;

	UFUNCTION()
	void CharacterTaskChanged(ECharacterTask NewTask);
	ECharacterTask CurrentCharacterTask;

	UFUNCTION()
	void CharacterStatusChanged(ECharacterStatus NewStatus);
	ECharacterStatus CurrentCharacterStatus;

	UFUNCTION()
	void CharacterNeedsChanged(ECharacterNeeds NewNeed);
	ECharacterNeeds CurrentCharacterNeed;

	UFUNCTION()
	void CharacterNewRoom(float Safety, float Environment, float Health);
	
	float RoomSafety;
	float RoomEnvironment;
	float RoomHealth;
};
