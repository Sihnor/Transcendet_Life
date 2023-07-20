// Copyright 2019 Tefel. All Rights Reserved

#include "GravityCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GravityMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/PostProcessComponent.h"
#include "Components/WidgetComponent.h"
#include "Transcendet_Life/Characters/GodHand.h"
#include "Transcendet_Life/UI/GravityCharacterHUDComponent.h"

#define ECC_Planet ECC_GameTraceChannel1
#define ECC_GravityCharacter ECC_GameTraceChannel2

AGravityCharacter::AGravityCharacter() {
  // Setting up the Capsule Component
  this->CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCompnent"));
  this->CapsuleComponent->InitCapsuleSize(55.0f, 96.0f);
  this->CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
  this->CapsuleComponent->CanCharacterStepUpOn = ECB_No;
  this->CapsuleComponent->SetShouldUpdatePhysicsVolume(true);
  this->CapsuleComponent->SetCanEverAffectNavigation(false);
  this->CapsuleComponent->bDynamicObstacle = true;
  this->SetRootComponent(this->CapsuleComponent);

  // Setting up the CharacterMesh
  this->TPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RobotMesh"));
  this->TPMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -110.0f));
  this->TPMesh->SetupAttachment(this->CapsuleComponent);
  this->TPMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
  this->TPMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
  this->TPMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Block);
  this->TPMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
  this->TPMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
  this->TPMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
  this->TPMesh->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Block);
  this->TPMesh->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Ignore);
  this->TPMesh->SetCollisionResponseToChannel(ECC_Destructible, ECR_Block);
  this->TPMesh->SetCollisionResponseToChannel(ECC_Planet, ECR_Block);
  this->TPMesh->SetCollisionObjectType(ECC_GravityCharacter);
  

  // Adding the ArrowComponent
  this->ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
  this->ArrowComponent->SetupAttachment(this->CapsuleComponent);

  // Create a CameraComponent	
  this->CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
  this->CameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
  this->CameraComponent->bUsePawnControlRotation = false;
  this->CameraComponent->SetupAttachment(this->CapsuleComponent);

  // Setting up the First Person Mesh
  this->FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
  this->FPMesh->SetRelativeLocation(FVector(-30.0f, 0.0f, -150.0f));
  this->FPMesh->SetupAttachment(this->CameraComponent);
  this->FPMesh->SetVisibility(false);

  // FIlling up the FloatingPawnMovement
  //this->CharacterMovement->NavAgentProps.AgentHeight = this->CapsuleComponent->GetScaledCapsuleHalfHeight();
  //this->CharacterMovement->NavAgentProps.AgentRadius = this->CapsuleComponent->GetScaledCapsuleRadius();
  this->CharacterMovement = CreateDefaultSubobject<UGravityMovementComponent>(TEXT("CharacterMovement"));

  // Setting up the HUD
  this->CharacterHUD = CreateDefaultSubobject<UGravityCharacterHUDComponent>(TEXT("CharacterMenu"));
  this->CharacterHUD->SetRelativeLocation(FVector(0.0f, 0.f, 100.f)); // Position the camera
  this->CharacterHUD->SetVisibility(false);
  this->CharacterHUD->SetupAttachment(this->CapsuleComponent);


  // Initialise Variables for Possesing
  this->bCanBePossessed = false;
  this->GodHand = nullptr;
}

UGravityMovementComponent* AGravityCharacter::GetGravityMovementComponent() {
  return this->CharacterMovement;
}

void AGravityCharacter::SetHasTool(const bool bHasNewTool) {
  this->bHasTool = bHasNewTool;
}

bool AGravityCharacter::GetHasTool() const {
  return this->bHasTool;
}


// Called when the game starts or when spawned
void AGravityCharacter::BeginPlay() {
  Super::BeginPlay();

  // Setting up Enhanced Player Input
  if (const APlayerController* PlayerController = Cast<APlayerController>(this->GetController())) {
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
      Subsystem->AddMappingContext(this->DefaultMappingContext, 0);
    }

    //UGravityCharacterHUDOLD* GravityCharacterHUD = Cast<UGravityCharacterHUDOLD>(this->CharacterHUD);
    //if (GravityCharacterHUD) {
    //  UE_LOG(LogTemp, Error, TEXT("IF"))
    //  GravityCharacterHUD->SetOwningDunked(this);
    //}
    //UE_LOG(LogTemp, Error, TEXT("ENDE"))
  }
}

// Called to bind functionality to input
void AGravityCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
  if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
    // Jumping
    EnhancedInputComponent->BindAction(this->JumpCharacterAction, ETriggerEvent::Started, this, &AGravityCharacter::Jump);
    EnhancedInputComponent->BindAction(this->JumpCharacterAction, ETriggerEvent::Completed, this, &AGravityCharacter::StopJumping);

    // Look
    EnhancedInputComponent->BindAction(this->LookCharacterAction, ETriggerEvent::Triggered, this, &AGravityCharacter::Look);

    // Move
    EnhancedInputComponent->BindAction(this->MoveCharacterAction, ETriggerEvent::Started, this, &AGravityCharacter::StartMove);
    EnhancedInputComponent->BindAction(this->MoveCharacterAction, ETriggerEvent::Triggered, this, &AGravityCharacter::Move);
    EnhancedInputComponent->BindAction(this->MoveCharacterAction, ETriggerEvent::Completed, this, &AGravityCharacter::StopMove);

    // UnPosses
    EnhancedInputComponent->BindAction(this->PossesAction, ETriggerEvent::Started, this, &AGravityCharacter::UnPosses);
  }
}

void AGravityCharacter::PreparePosses(AGodHand* God) {
  // Get the Pointer for the GodHand
  this->GodHand = God;

  // Add the MappingContext of the Character
  if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Cast<APlayerController>(this->Controller)->GetLocalPlayer())) {
    Subsystem->AddMappingContext(this->DefaultMappingContext, 0);
  }

  // Switch from THird to first person view
  this->TPMesh->SetVisibility(false);
  this->FPMesh->SetVisibility(true);
}

void AGravityCharacter::Look(const FInputActionValue& Value) {
  // input is a Vector2D
  const FVector2D LookAxisVector = Value.Get<FVector2D>();

  if (this->GetController() != nullptr) {
    // add yaw and pitch input to controller
    float YawValue = LookAxisVector.Y * -1.0f;
    const float CheckBoarder = YawValue + this->CameraComponent->GetRelativeRotation().Pitch;
    
    if (CheckBoarder > 89.0f || CheckBoarder < -89.0f) {
      YawValue = 0.0f;
    }
    
    this->CameraComponent->AddRelativeRotation(FRotator(YawValue, 0.0f, 0.0f));
    this->AddActorLocalRotation(FRotator(0.0f, LookAxisVector.X, 0.0f));
  }
}

void AGravityCharacter::Move(const FInputActionValue& Value) {
  // input is a Vector2D
  const FVector2D MovementVector = Value.Get<FVector2D>();
  if (this->GetController() != nullptr) {
    // add movement
    this->AddMovementInput(this->GetTPMesh()->GetForwardVector(), -1.0f * MovementVector.X);
    this->AddMovementInput(this->GetTPMesh()->GetRightVector(), MovementVector.Y);
  }
}

void AGravityCharacter::StartMove(const FInputActionValue& Value) {
  this->GetGravityMovementComponent()->StartMoving();
}
void AGravityCharacter::StopMove(const FInputActionValue& Value) {
  this->GetGravityMovementComponent()->StopMoving();
}

void AGravityCharacter::UnPosses(const FInputActionValue& Value) {
  
  if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Cast<APlayerController>(this->Controller)->GetLocalPlayer())) {
    Subsystem->RemoveMappingContext(this->DefaultMappingContext);
  }
  this->Controller->Possess(this->GodHand);
  this->GodHand->PreparePosses();

  // Switch from first to third person view
  this->TPMesh->SetVisibility(true);
  this->FPMesh->SetVisibility(false);
  
  this->GodHand = nullptr;
}

void AGravityCharacter::Jump(const FInputActionValue& Value) {
  this->CharacterMovement->StartJumping();
}

void AGravityCharacter::StopJumping(const FInputActionValue& Value) {
  this->CharacterMovement->StopJumping();
}
