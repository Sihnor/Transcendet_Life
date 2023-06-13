// Fill out your copyright notice in the Description page of Project Settings.

#include "GodHand.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"
#include "Camera/CameraComponent.h"
#include "Components/RectLightComponent.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGodHand::AGodHand() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup component hierarchy
	this->Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(this->Root);

	this->PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMeshComp"));
	this->PlayerMesh->SetRelativeRotation(FRotator3d(0, 180, 0));
	this->PlayerMesh->SetRelativeScale3D(FVector(0.05));
	this->PlayerMesh->SetupAttachment(this->Root);

	this->SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	this->SpringArm->SetRelativeRotation(FRotator(-30, 0, 0));
	this->SpringArm->TargetArmLength = 150;
	this->SpringArm->SetupAttachment(this->Root);

	this->RectLightComponent = CreateDefaultSubobject<URectLightComponent>(TEXT("Light"));
	this->RectLightComponent->SetRelativeLocation(FVector(100, 0, 120));
	this->RectLightComponent->Intensity = 10;
	this->RectLightComponent->SetupAttachment(this->SpringArm);

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
	this->GetRotaingWorldFormAllActors();
}

// Called every frame
void AGodHand::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AGodHand::GetRotaingWorldFormAllActors() {
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors) {
		AStaticMeshActor* StaticMeshActor = Cast<AStaticMeshActor>(Actor);
		if (StaticMeshActor != nullptr) {
			FString Text = StaticMeshActor->GetName();
		}
		if (StaticMeshActor != nullptr && StaticMeshActor->GetName() == "StaticMeshActor_6") {
			this->RotatingObject = StaticMeshActor;
			break;
		}
	}
}

// Called to bind functionality to input
void AGodHand::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(this->MoveWorldAction, ETriggerEvent::Triggered, this, &AGodHand::MoveWorld);
	}
}

void AGodHand::MoveWorld(const FInputActionValue& Value) {
	// Check if Object is Valid
	if (!this->RotatingObject) {
		return;
	}
	
	// Convert Paramter in a 2D Vector
	const FVector2D CurrentValue = Value.Get<FVector2D>();
	
	constexpr float RotationSpeed = 0.5f;

	
	const float RotationDeltaYaw = CurrentValue.X  * RotationSpeed * GetWorld()->GetDeltaSeconds();
	const float RotationDeltaPitch = (CurrentValue.Y * -1) * RotationSpeed * GetWorld()->GetDeltaSeconds();

	// Calculate the Quaternion for the Rotations based on the Deltas
	const FQuat YawRotation = FQuat(FVector::UpVector, RotationDeltaYaw); 
	const FQuat PitchRotation = FQuat(FVector::RightVector, RotationDeltaPitch);
	
	const FQuat CombinedRotation = YawRotation * PitchRotation;
	
	this->RotatingObject->AddActorWorldRotation(CombinedRotation.Rotator());
}
