﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "GodHand.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Transcendet_Life/BaseClasses/GravityPlanet.h"


// Sets default values
AGodHand::AGodHand() {
  // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  this->SetActorRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));

  // Setup component hierarchy
  this->Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
  SetRootComponent(this->Root);

  // Setup the PlayerMesh
  this->PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMeshComp"));
  this->PlayerMesh->SetRelativeRotation(FRotator3d(0, 180, 0));
  this->PlayerMesh->SetRelativeScale3D(FVector(0.05));
  this->PlayerMesh->SetupAttachment(this->Root);

  // Attach a SpringArm for the Camera
  this->SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
  //this->SpringArm->SetRelativeRotation(FRotator(-30, 0, 0));
  this->SpringArm->SetRelativeRotation(FRotator(0, 0, 0));
  this->SpringArm->TargetArmLength = 150;
  this->SpringArm->SetupAttachment(this->Root);

  // Setup the PlayerCamera
  this->PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCameraComp"));
  this->PlayerCamera->SetupAttachment(this->SpringArm);
  this->PlayerCamera->FieldOfView = 40.0f;

  AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AGodHand::BeginPlay() {
  Super::BeginPlay();

  // Setting up the Enhanced Player Input
  if (const APlayerController* PlayerController = Cast<APlayerController>(this->GetController())) {
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
      UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
      Subsystem->AddMappingContext(this->MappingContext, 0);
    }
  }

  // Get the all Actor from World
  this->GetRotatingWorldFormAllActors();
}

// Called every frame
void AGodHand::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

  

  FHitResult HitResult;
  FCollisionQueryParams CollisionParams;
  FVector Start = this->PlayerMesh->GetComponentLocation();
  FVector End = this->PlayerMesh->GetForwardVector();
  this->ActorLineTraceSingle(HitResult, Start, End, ECC_Visibility, CollisionParams);
  DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red, false, 0.1f, 0, 1.0f);
}

void AGodHand::GetRotatingWorldFormAllActors() {
  TArray<AActor*> FoundActors;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGravityPlanet::StaticClass(), FoundActors);
  for (AActor* Actor : FoundActors) {
    AGravityPlanet* PlanetActor = Cast<AGravityPlanet>(Actor);
    if (PlanetActor != nullptr) {
      FString Text = PlanetActor->GetName();
    }
    if (PlanetActor != nullptr && PlanetActor->GetName() == "PlanetActor") {
      //this->RotatingObject = PlanetActor;

      break;
    }
  }
}

// Called to bind functionality to input
void AGodHand::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);

  if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
    EnhancedInputComponent->BindAction(this->RotatePlanetAction, ETriggerEvent::Triggered, this, &AGodHand::RotatePlanet);
    EnhancedInputComponent->BindAction(this->ZoomPlanetAction, ETriggerEvent::Triggered, this, &AGodHand::ZoomPlanet);
    EnhancedInputComponent->BindAction(this->MoveHandMeshAction, ETriggerEvent::Triggered, this, &AGodHand::MoveHandMesh);
  }
}

void AGodHand::RotatePlanet(const FInputActionValue& Value) {
  // Check if Object is Valid
  if (!this->RotatingObject) {
    return;
  }

  this->RotatingObject->RotatePlanet(Value);
}

void AGodHand::ZoomPlanet(const FInputActionValue& Value) {
  const FVector StartLocation = this->PlayerMesh->GetComponentLocation();
  const FVector ShootDirection = this->PlayerMesh->GetForwardVector();
  const FVector PlanetWorldLocation = this->RotatingObject->GetActorLocation() - this->GetActorLocation();
  const FVector EndLocation = StartLocation + ShootDirection * PlanetWorldLocation.Length() * -1.0;

  if (FHitResult HitResult; this->RotatingObject->ActorLineTraceSingle(HitResult, StartLocation, EndLocation, ECC_Visibility, FCollisionQueryParams(FName(TEXT("Raycast")), false))) {
    constexpr float ZoomScale = 100.0f;

    float Distance = HitResult.Distance;
    
    // Stop before the the Actor will be in the planet
    if (constexpr float MinZoomDistance = 150.0f; Distance + Value.Get<float>() * ZoomScale < MinZoomDistance && Value.Get<float>() < 0) {
      return;
    }
    
    // Stop at a specific distance
    if (constexpr float MaxZoomDistance = 2500.0f; Distance + Value.Get<float>() * ZoomScale > MaxZoomDistance && Value.Get<float>() > 0) {
      return;
    }

    FVector FutureLocation = this->PlayerMesh->GetForwardVector().GetSafeNormal() * Value.Get<float>() * ZoomScale;
    const float ScaleFactor = (Distance + FutureLocation.Length() * Value.Get<float>()) / 20;

    this->PlayerMesh->SetRelativeScale3D(FVector(1.0f / ScaleFactor, 1.0f / ScaleFactor, 1.0f / ScaleFactor));
    
    this->Root->AddRelativeLocation(FutureLocation);
  }
}

void AGodHand::MoveHandMesh(const FInputActionValue& Value) {
   if (const UGameViewportClient* ViewportClient = GEngine->GameViewport) {
    // Get the Mouse Position from the Viewport
    FVector2D MousePosition;

    const bool bMousePositionValid = ViewportClient->GetMousePosition(MousePosition);
    if (bMousePositionValid) {
      FVector2D ViewportSize;
      ViewportClient->GetViewportSize(ViewportSize);

      // Clamping the mouse position to prevent the mesh from moving out too far of the viewport 
      MousePosition.X = FMath::Clamp(MousePosition.X, 0.05 * ViewportSize.X, 0.95 * ViewportSize.X);
      MousePosition.Y = FMath::Clamp(MousePosition.Y, 0.1 * ViewportSize.Y, 0.95 * ViewportSize.Y);

      // Get the width and height inside the field of View from the Camera to the end of the SpringArm
      const float HalfWidthFromFOV = (tan((this->PlayerCamera->FieldOfView / 2) * PI / 180) * this->SpringArm->
                                                                                                    TargetArmLength);
      const float HeightFromFOV = 2 * HalfWidthFromFOV * (ViewportSize.Y / ViewportSize.X);

      // Calculate the start points for the movement for the mesh
      const float StartPointFromFOVAndSpringArmForWidth = this->SpringArm->GetRelativeLocation().Y - HalfWidthFromFOV;
      const float StartPointFromFOVAndSpringArmForHeightForZ = this->SpringArm->GetRelativeLocation().Z - HeightFromFOV
        / 2;
      const float StartPointFromFOVAndSpringArmForHeightForX = this->SpringArm->GetRelativeLocation().X + sin(
        this->SpringArm->GetRelativeRotation().Pitch * PI / 180) * HeightFromFOV / 2;

      // Create and get the percentage of the mouse position from the Viewport width and height. 
      FVector2D MousePositionPercentage;
      MousePositionPercentage.X = (100 / ViewportSize.X) * (MousePosition.X / 100);
      MousePositionPercentage.Y = (100 / ViewportSize.Y) * (MousePosition.Y / 100);

      //  Set the Vector of the MeshLocation to the value of the percentage of the width and height
      FVector3d NewMeshLocation;
      NewMeshLocation.Y = (MousePositionPercentage.X * 2 * HalfWidthFromFOV) + StartPointFromFOVAndSpringArmForWidth;
      NewMeshLocation.X = (MousePositionPercentage.Y) * StartPointFromFOVAndSpringArmForHeightForX - (1 -
        MousePositionPercentage.Y) * StartPointFromFOVAndSpringArmForHeightForX;
      NewMeshLocation.Z = ((1 - MousePositionPercentage.Y) * HeightFromFOV) +
        StartPointFromFOVAndSpringArmForHeightForZ; // 1- cause to invert the movement

      this->PlayerMesh->SetRelativeLocation(NewMeshLocation);
    }
  }
}
