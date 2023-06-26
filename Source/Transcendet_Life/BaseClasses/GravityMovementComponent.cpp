#include "GravityMovementComponent.h"

UGravityMovementComponent::UGravityMovementComponent() {
  
}

bool UGravityMovementComponent::IsCrouching() const {
  return false;
}

bool UGravityMovementComponent::IsFalling() const {
  return false;
}

bool UGravityMovementComponent::IsMovingOnGround() const {
  return false;
}

bool UGravityMovementComponent::IsSwimming() const {
  return false;
}

bool UGravityMovementComponent::IsFlying() const {
  return false;
  
}

void UGravityMovementComponent::AddInputVector(FVector WorldVector, bool bForce) {
  
  FVector GravityDirection = WorldVector;
  if (this->bIsJumping) {
    // Setup the antigravity
    GravityDirection = FVector(this->GetPawnOwner()->GetActorUpVector());
    
    // CHeck if end jump max height is reached set default Vector
    if ((this->StartJumpHeight + JumpHeight) < (this->GetActorLocation() - this->GetPlanetCenter()).Length() ) {
      GravityDirection = WorldVector;
      this->StopJumping();
    }
  }


  Super::AddInputVector(GravityDirection, bForce);
}

void UGravityMovementComponent::StartJumping() {
  if (!this->bIsJumping) {
    this->StartJumpHeight = (this->GetActorLocation() - this->GetPlanetCenter()).Length();
    this->bIsJumping = true;
  }
}

bool UGravityMovementComponent::CanJump() {
  return false;
}
void UGravityMovementComponent::StopJumping() {
  this->bIsJumping = false;
}

void UGravityMovementComponent::SetPlanetCenter(const FVector& Center) {
  this->PlanetCenter = Center;
}
void UGravityMovementComponent::SetCharacterHasGravity(bool HasGravity) {
  this->bHasGravity = HasGravity;
}

FVector UGravityMovementComponent::GetPlanetCenter() {
  return this->PlanetCenter;
}
bool UGravityMovementComponent::GetCharacterHasGravity() {
  return this->bHasGravity;
}

bool UGravityMovementComponent::IsJumping() {
  return  this->bIsJumping;
}
