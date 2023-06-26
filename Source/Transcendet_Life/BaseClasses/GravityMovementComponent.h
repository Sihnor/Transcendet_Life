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

	virtual bool IsCrouching() const override;
	virtual bool IsFalling() const override;
	virtual bool IsMovingOnGround() const override;
	virtual bool IsSwimming() const override;
	virtual bool IsFlying() const override;
	virtual void AddInputVector(FVector WorldVector, bool bForce) override;

public:
	void StartJumping();
	void StopJumping();
	bool CanJump();
	
	
	
	
	

	
	void SetPlanetCenter(const FVector& Center);
	void SetCharacterHasGravity(bool HasGravity);
	FVector GetPlanetCenter();
	bool GetCharacterHasGravity();

	bool IsJumping();

private:
	FVector PlanetCenter = FVector::Zero();

	bool bIsJumping = false;
	bool bHasGravity = false;
	float JumpHeight = 100.0f;
	float StartJumpHeight = 0.0f;
};
