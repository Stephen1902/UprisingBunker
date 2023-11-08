// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "NeedsComponent.h"
#include "HygieneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPRISINGBUNKER_API UHygieneComponent : public UNeedsComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHygieneComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
