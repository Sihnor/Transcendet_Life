// Fill out your copyright notice in the Description page of Project Settings.


#include "Profession.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AProfession::AProfession() {
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  // Create a CameraComponent	
  this->FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
  this->FirstPersonCameraComponent->SetupAttachment(this->GetCapsuleComponent());
  this->FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
  this->FirstPersonCameraComponent->bUsePawnControlRotation = true;

  // Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
  this->Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
  this->Mesh1P->SetOnlyOwnerSee(true);
  this->Mesh1P->SetupAttachment(this->FirstPersonCameraComponent);
  this->Mesh1P->bCastDynamicShadow = false;
  this->Mesh1P->CastShadow = false;
  this->Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

// Called when the game starts or when spawned
void AProfession::BeginPlay() {
  Super::BeginPlay();

  // Setting up Enhanced Player Input
  if (const APlayerController* PlayerController = Cast<APlayerController>(this->GetController())) {
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
      Subsystem->AddMappingContext(this->DefaultMappingContext, 0);
    }
  }

  UCharacterMovementComponent* CharacterMovementComponent = this->GetCharacterMovement();
  CharacterMovementComponent->SetPlaneConstraintNormal(FVector(0.0,0.0,1.0));
  
}

// Called every frame
void AProfession::Tick(const float DeltaTime) {
  Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AProfession::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
  if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
    // Jumping
    EnhancedInputComponent->BindAction(this->JumpCharacterAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
    EnhancedInputComponent->BindAction(this->JumpCharacterAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

    // Look
    EnhancedInputComponent->BindAction(this->LookCharacterAction, ETriggerEvent::Triggered, this, &AProfession::Look);

    // Move
    EnhancedInputComponent->BindAction(this->MoveCharacterAction, ETriggerEvent::Triggered, this, &AProfession::Move);
  }
}

void AProfession::Look(const FInputActionValue& Value) {
  // input is a Vector2D
  const FVector2D LookAxisVector = Value.Get<FVector2D>();

  if (this->GetController() != nullptr) {
    // add yaw and pitch input to controller
    this->AddControllerYawInput(LookAxisVector.X);
    this->AddControllerPitchInput(LookAxisVector.Y);
  }
}

void AProfession::Move(const FInputActionValue& Value) {
  // input is a Vector2D
  const FVector2D MovementVector = Value.Get<FVector2D>();

  if (this->GetController() != nullptr) {
    // add movement 
    this->AddMovementInput(this->GetActorForwardVector(), MovementVector.Y);
    this->AddMovementInput(this->GetActorRightVector(), MovementVector.X);
  }
}

void AProfession::SetHasTool(const bool bHasNewTool) {
  this->bHasTool = bHasNewTool;
}

bool AProfession::GetHasTool() const {
  return this->bHasTool;
}
