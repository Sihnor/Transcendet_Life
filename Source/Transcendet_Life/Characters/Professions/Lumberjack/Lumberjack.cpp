// Fill out your copyright notice in the Description page of Project Settings.


#include "Lumberjack.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"


// Sets default values
ALumberjack::ALumberjack() {
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  // Character doesnt have a axe at start
  this->bHasAxe = false;

  // Create a CameraComponent	
  this->FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
  this->FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
  this->FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
  this->FirstPersonCameraComponent->bUsePawnControlRotation = true;

  // Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
  Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
  Mesh1P->SetOnlyOwnerSee(true);
  Mesh1P->SetupAttachment(FirstPersonCameraComponent);
  Mesh1P->bCastDynamicShadow = false;
  Mesh1P->CastShadow = false;
  //Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
  Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
  
  //// Setup for the right position and rotation for the right pose
  //this->GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
  //this->GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, 70.0));
  //this->SetActorScale3D(FVector(0.1));

  AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ALumberjack::BeginPlay() {
  Super::BeginPlay();

  // Setting up Enhanced Player Input
  if (const APlayerController* PlayerController = Cast<APlayerController>(this->GetController())) {
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
      Subsystem->AddMappingContext(this->DefaultMappingContext, 0);
    }
  }
}

// Called every frame
void ALumberjack::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ALumberjack::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);

  if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
    // Jumping
    EnhancedInputComponent->BindAction(this->JumpCharacterAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
    EnhancedInputComponent->BindAction(this->JumpCharacterAction, ETriggerEvent::Triggered, this, &ACharacter::StopJumping);
    
    // Look
    EnhancedInputComponent->BindAction(this->LookCharacterAction, ETriggerEvent::Triggered, this, &ALumberjack::Look);
    
    // Move
    EnhancedInputComponent->BindAction(this->MoveCharacterAction, ETriggerEvent::Triggered, this, &ALumberjack::Move);
  }
}


void ALumberjack::SetHasAxe(const bool bNewHasAxe) {
  this->bHasAxe = bNewHasAxe;
}

bool ALumberjack::GetHasAxe() {
  return this->bHasAxe;
}

void ALumberjack::Look(const FInputActionValue& Value) {
  // input is a Vector2D
  const FVector2D LookAxisVector = Value.Get<FVector2D>();

  if (this->GetController() != nullptr) {
    // add yaw and pitch input to controller
    this->AddControllerYawInput(LookAxisVector.X);
    this->AddControllerPitchInput(LookAxisVector.Y);
  }
}

void ALumberjack::Move(const FInputActionValue& Value) {
  // input is a Vector2D
  const FVector2D MovementVector = Value.Get<FVector2D>();

  if (this->GetController() != nullptr) {
    // add movement 
    this->AddMovementInput(this->GetActorForwardVector(), MovementVector.Y);
    this->AddMovementInput(this->GetActorRightVector(), MovementVector.X);
  }
}
