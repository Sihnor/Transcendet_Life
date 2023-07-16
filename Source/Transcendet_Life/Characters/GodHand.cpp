// Fill out your copyright notice in the Description page of Project Settings.

#define ECC_Planet ECC_GameTraceChannel1
#define ECC_GravityCharacter ECC_GameTraceChannel2

#include "GodHand.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Transcendet_Life/BaseClasses/GravityCharacter.h"
#include "Transcendet_Life/BaseClasses/GravityPlanet.h"


// Sets default values
AGodHand::AGodHand() {
  // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
  this->bIsOverlapped = false;

  this->SetActorRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));

  // Setup component hierarchy
  this->Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
  SetRootComponent(this->Root);

  this->SelectionOverlap = CreateDefaultSubobject<UBoxComponent>(TEXT("DecalBox"));
  this->SelectionOverlap->SetRelativeLocation(FVector(40.0f, 0.0f, 0.0f));
  this->SelectionOverlap->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
  this->SelectionOverlap->SetRelativeScale3D(FVector(0.2f));
  this->SelectionOverlap->SetBoxExtent(FVector(128.0f, 256.0f, 256.0f));
  this->SelectionOverlap->OnComponentEndOverlap.AddDynamic(this, &AGodHand::OnDecalEndOverlap);
  this->SelectionOverlap->SetupAttachment(this->Root);

  this->Selection = CreateDefaultSubobject<UDecalComponent>(TEXT("Pointer"));
  this->Selection->DecalSize = FVector(128.0f, 256.0f, 256.0f);
  this->Selection->SetupAttachment(this->SelectionOverlap);


  // Setup the PlayerMesh
  this->PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMeshComp"));
  this->PlayerMesh->SetRelativeRotation(FRotator3d(0, 180, 0));
  this->PlayerMesh->SetRelativeScale3D(FVector(0.05));
  this->PlayerMesh->SetupAttachment(this->Root);
  this->PlayerMesh->SetVisibility(true);
  
  
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

  this->SelectedPlayer = nullptr;
  this->bIsPossessing = false;
  
}

// Called when the game starts or when spawned
void AGodHand::BeginPlay() {
  Super::BeginPlay();

  const FVector StartLocation = this->SpringArm->GetComponentLocation();
  const FVector ShootDirection = this->SpringArm->GetForwardVector();
  const FVector EndLocation = StartLocation + ShootDirection * 10000;
  FHitResult HitResult;
  if (GetWorld()->LineTraceSingleByObjectType(HitResult, StartLocation, EndLocation, ECC_Planet)) {
    this->RotatingObject = Cast<AGravityPlanet>(HitResult.GetActor());
  }

  if (APlayerController* PlayerController = Cast<APlayerController>(this->Controller)) {
    PlayerController->bEnableClickEvents = true;
    //PlayerController->bShowMouseCursor = true;
  }

  // Setting up the Enhanced Player Input
  if (const APlayerController* PlayerController = Cast<APlayerController>(this->GetController())) {
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
      Subsystem->AddMappingContext(this->MappingContext, 0);
    }
  }

  // Get the all Actor from World
  this->GetRotatingWorldFormAllActors();
}

void AGodHand::OnDecalEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Actor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
  // Setting the outline to false
  AGravityCharacter* Character = Cast<AGravityCharacter>(Actor);
  if (Character) {
    //Character->Outliner->SetVisibility(false);
    //Character->Outliner->SetActive(false);
    Character->CharacterMesh->CustomDepthStencilValue = 1;
  }
}

// Called every frame
void AGodHand::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);
  
  this->MoveDecal();  
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
    EnhancedInputComponent->BindAction(this->MoveHandMeshAction, ETriggerEvent::Triggered, this, &AGodHand::MoveCursor);
    EnhancedInputComponent->BindAction(this->InteractAction, ETriggerEvent::Started, this, &AGodHand::Interact);
    EnhancedInputComponent->BindAction(this->PossesAction, ETriggerEvent::Started, this, &AGodHand::Possess);
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
  // Check if Object is Valid
  if (!this->RotatingObject) {
    return;
  }
  
  const FVector StartLocation = this->SpringArm->GetComponentLocation();
  const FVector ShootDirection = this->SpringArm->GetForwardVector();
  const FVector PlanetWorldLocation = this->RotatingObject->GetActorLocation() - this->GetActorLocation();
  const FVector EndLocation = StartLocation + ShootDirection * PlanetWorldLocation.Length();
  FHitResult HitResult;
  if (GetWorld()->LineTraceSingleByObjectType(HitResult, StartLocation, EndLocation, ECC_Planet)) {
    constexpr float ZoomScale = 100.0f;

    float Distance = HitResult.Distance;

    // Stop before the the Actor will be in the planet
    if (constexpr float MinZoomDistance = 150.0f; Distance - Value.Get<float>() * ZoomScale < MinZoomDistance && Value.Get<float>() > 0) {
      return;
    }

    // Stop at a specific distance
    if (constexpr float MaxZoomDistance = 2500.0f; Distance - Value.Get<float>() * ZoomScale > MaxZoomDistance && Value.Get<float>() < 0) {
      return;
    }

    FVector FutureLocation = this->SpringArm->GetForwardVector().GetSafeNormal() * Value.Get<float>() * ZoomScale;
    const float ScaleFactor = (Distance + FutureLocation.Length() * Value.Get<float>()) / 20;

    this->PlayerMesh->SetRelativeScale3D(FVector(1.0f / ScaleFactor, 1.0f / ScaleFactor, 1.0f / ScaleFactor));

    this->Root->AddRelativeLocation(FutureLocation);
  }
}

void AGodHand::MoveCursor(const FInputActionValue& Value) {
  this->MoveHandMesh();
}

void AGodHand::Interact(const FInputActionValue& Value) {
  
  // Unselect the last selected Character
  if (this->SelectedPlayer != nullptr) {
    this->SelectedPlayer->bCanBePossessed = false;
    this->SelectedPlayer->CharacterHUD->SetVisibility(false);
    this->SelectedPlayer = nullptr;
  }
  
  // Wandle die Bildschirmkoordinaten in Weltkoordinaten um
  FVector2D MousePosition;
  
  bool bGotMousePosition = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MousePosition.X, MousePosition.Y);

  if (bGotMousePosition) {
    FHitResult HitResult;
    FVector CameraLocation;
    FVector WorldDirection;
    
    UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, CameraLocation, WorldDirection);
    
    // Save the if a there is a selected player
    if (GetWorld()->LineTraceSingleByObjectType(HitResult, CameraLocation, CameraLocation + WorldDirection * 10000, ECC_GravityCharacter) ){
      
      this->SelectedPlayer = Cast<AGravityCharacter>(HitResult.GetActor());
    
      this->SelectedPlayer->bCanBePossessed = true;
      this->SelectedPlayer->CharacterHUD->SetVisibility(true);
    }
  }


  
  

}

void AGodHand::Possess(const FInputActionValue& Value) {
  // Start the Posses process
  if (this->SelectedPlayer) {
    // Remove the GOdhand Mapping COntext
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Cast<APlayerController>(this->Controller)->GetLocalPlayer())) {
      Subsystem->RemoveMappingContext(this->MappingContext);
    }
    // posses and Add the new Mapping Context 
    this->Controller->Possess(this->SelectedPlayer);
    this->SelectedPlayer->PreparePosses(this);
    this->bIsPossessing = true;
  }
}

void AGodHand::PreparePosses() {
  // Adding the new MappingContext
  if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Cast<APlayerController>(this->Controller)->GetLocalPlayer())) {
    Subsystem->AddMappingContext(this->MappingContext, 0);
  }
  this->bIsPossessing = false;
}

void AGodHand::MoveHandMesh() const {
  // Stop moving the hand mesh if player is possesing a character
  if (bIsPossessing) {
    return;
  }
  
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
      const float HalfWidthFromFOV = (tan((this->PlayerCamera->FieldOfView / 2) * PI / 180) * this->SpringArm->TargetArmLength);
      const float HeightFromFOV = 2 * HalfWidthFromFOV * (ViewportSize.Y / ViewportSize.X);

      // Calculate the start points for the movement for the mesh
      const float StartPointFromFOVAndSpringArmForWidth = this->SpringArm->GetRelativeLocation().Y - HalfWidthFromFOV;
      const float StartPointFromFOVAndSpringArmForHeightForZ = this->SpringArm->GetRelativeLocation().Z - HeightFromFOV / 2;
      const float StartPointFromFOVAndSpringArmForHeightForX = this->SpringArm->GetRelativeLocation().X + sin(this->SpringArm->GetRelativeRotation().Pitch * PI / 180) * HeightFromFOV / 2;


      const float MousePositionRatioX = (MousePosition.X - ViewportSize.X / 2.0f) / ViewportSize.X / 2.0f;
      const float MousePositionRatioY = (MousePosition.Y - ViewportSize.Y / 2.0f) / ViewportSize.Y / 2.0f;

      const FRotator NewRotator = FRotator(MousePositionRatioY * 40.0f, MousePositionRatioX * 40.0f + 180, this->PlayerMesh->GetRelativeRotation().Roll);
      this->PlayerMesh->SetRelativeRotation(NewRotator);

      // Create and get the percentage of the mouse position from the Viewport width and height. 
      FVector2D MousePositionPercentage;
      MousePositionPercentage.X = (100 / ViewportSize.X) * (MousePosition.X / 100);
      MousePositionPercentage.Y = (100 / ViewportSize.Y) * (MousePosition.Y / 100);

      //  Set the Vector of the MeshLocation to the value of the percentage of the width and height
      FVector3d NewMeshLocation;
      NewMeshLocation.Y = (MousePositionPercentage.X * 2 * HalfWidthFromFOV) + StartPointFromFOVAndSpringArmForWidth;
      NewMeshLocation.X = (MousePositionPercentage.Y) * StartPointFromFOVAndSpringArmForHeightForX - (1 - MousePositionPercentage.Y) * StartPointFromFOVAndSpringArmForHeightForX;
      NewMeshLocation.Z = ((1 - MousePositionPercentage.Y) * HeightFromFOV) + StartPointFromFOVAndSpringArmForHeightForZ; // 1- cause to invert the movement

      this->PlayerMesh->SetRelativeLocation(NewMeshLocation);
    }
  }
}

void AGodHand::MoveDecal() const {
  // Stop moving the hand mesh if player is possesing a character
  if (bIsPossessing) {
    return;
  }
  
  // Hole die aktuelle Mausposition auf dem Viewport
  FVector2D MousePosition;
  bool bGotMousePosition = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MousePosition.X, MousePosition.Y);
  
  if (bGotMousePosition) {
    // Wandle die Bildschirmkoordinaten in Weltkoordinaten um
    FHitResult HitResult;
    FVector CameraLocation;
    FVector WorldDirection;
    UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, CameraLocation, WorldDirection);

    // Get the Position for the decal on the Planet
    if (GetWorld()->LineTraceSingleByObjectType(HitResult, CameraLocation, CameraLocation + WorldDirection * 10000, ECC_Planet)) {
      FVector WorldMousePosition;
      WorldMousePosition = HitResult.Location;
      
      this->SelectionOverlap->SetWorldLocation(WorldMousePosition);
      this->SelectionOverlap->SetWorldRotation(HitResult.Normal.Rotation());
    }
  }
}
