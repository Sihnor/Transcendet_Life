#pragma once
#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GravityMovementComponent.generated.h"

// Custom gravity movement component which moves provides directional gravity movement
UCLASS()
class TRANSCENDET_LIFE_API UGravityMovementComponent : public UFloatingPawnMovement
{
	GENERATED_BODY()
	
	UGravityMovementComponent();


	
};
