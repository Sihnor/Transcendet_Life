// Copyright 2019 Tefel. All Rights Reserved

#include "GravityCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"


AGravityCharacter::AGravityCharacter() {
  this->CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCompnent"));
  this->CapsuleComponent->InitCapsuleSize(34.0f, 88.0f);
  this->CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
  this->CapsuleComponent->CanCharacterStepUpOn = ECB_No;
  this->CapsuleComponent->SetShouldUpdatePhysicsVolume(true);
  this->CapsuleComponent->SetCanEverAffectNavigation(false);
  this->CapsuleComponent->bDynamicObstacle = true;
  this->SetRootComponent(this->CapsuleComponent);

  this->CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RobotMesh"));
  this->CharacterMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -110.0f));
  this->CharacterMesh->SetupAttachment(this->CapsuleComponent);

  this->ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
  this->ArrowComponent->SetupAttachment(this->CapsuleComponent);

  // Attach a SpringArm for the Camera
  this->SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
  //this->SpringArm->SetRelativeRotation(FRotator(-30, 0, 0)); // For the tilted view
  this->SpringArm->SetRelativeRotation(FRotator(0, 0, 0));
  this->SpringArm->TargetArmLength = 300;
  this->SpringArm->bDoCollisionTest = false;
  this->SpringArm->SetupAttachment(this->GetCapsuleComponent());

  // Create a CameraComponent	
  this->CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
  this->CameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
  this->CameraComponent->bUsePawnControlRotation = true;
  this->CameraComponent->bUsePawnControlRotation = false;
  this->CameraComponent->SetupAttachment(this->SpringArm);

  this->CharacterMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("CharacterMovement"));
}

UFloatingPawnMovement* AGravityCharacter::GetFloatingMovementComponent() {
  return this->CharacterMovement;
}

// Called when the game starts or when spawned
void AGravityCharacter::BeginPlay() {
  Super::BeginPlay();

  // Setting up Enhanced Player Input
  if (const APlayerController* PlayerController = Cast<APlayerController>(this->GetController())) {
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
      Subsystem->AddMappingContext(this->DefaultMappingContext, 0);
    }
  }
}

// Called to bind functionality to input
void AGravityCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
  if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
    // Jumping
    EnhancedInputComponent->BindAction(this->JumpCharacterAction, ETriggerEvent::Triggered, this, &AGravityCharacter::Jump);
    EnhancedInputComponent->BindAction(this->JumpCharacterAction, ETriggerEvent::Completed, this, &AGravityCharacter::StopJumping);

    // Look
    EnhancedInputComponent->BindAction(this->LookCharacterAction, ETriggerEvent::Triggered, this, &AGravityCharacter::Look);

    // Move
    EnhancedInputComponent->BindAction(this->MoveCharacterAction, ETriggerEvent::Triggered, this, &AGravityCharacter::Move);
  }
}

void AGravityCharacter::Look(const FInputActionValue& Value) {
  // input is a Vector2D
  const FVector2D LookAxisVector = Value.Get<FVector2D>();

  if (this->GetController() != nullptr) {
    // add yaw and pitch input to controller
    this->SpringArm->AddRelativeRotation(FRotator(LookAxisVector.Y * -1.0, 0.0f,0.0f));
    this->AddActorLocalRotation(FRotator(0.0f, LookAxisVector.X,0.0f));
  }
}

void AGravityCharacter::Move(const FInputActionValue& Value) {
  // input is a Vector2D
  const FVector2D MovementVector = Value.Get<FVector2D>();
  if (this->GetController() != nullptr) {
    // add movement
    this->AddMovementInput(this->GetCharacterMesh()->GetForwardVector(), -1.0f * MovementVector.X);
    this->AddMovementInput(this->GetCharacterMesh()->GetRightVector(), MovementVector.Y);
  }
}

void AGravityCharacter::Jump(const FInputActionValue& Value) {}

void AGravityCharacter::StopJumping(const FInputActionValue& Value) {}

void AGravityCharacter::SetPlanetCenter(const FVector& Center) {
  this->PlanetCenter = Center;
}

void AGravityCharacter::SetCharacterHasGravity(const bool HasGravity) {
  this->bHasGravity = HasGravity;
}
