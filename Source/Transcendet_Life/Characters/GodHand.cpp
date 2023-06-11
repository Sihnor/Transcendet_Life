// Fill out your copyright notice in the Description page of Project Settings.



#include "GodHand.h"
#include "Camera/CameraComponent.h"
#include <Components/StaticMeshComponent.h>
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputTriggers.h"

// Sets default values
AGodHand::AGodHand() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setting up the Enhanced Player Input
	// Get Player Controller
	APlayerController* PlayerController = Cast<APlayerController>(this->GetController());
	if (PlayerController) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem) {
			Subsystem->AddMappingContext(this->MappingContext,0);
		}
	}

	// Setup component hierarchy
	this->PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	RootComponent = PlayerMesh;
	this->PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	this->PlayerCamera->SetupAttachment(this->PlayerMesh);
}

// Called when the game starts or when spawned
void AGodHand::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void AGodHand::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGodHand::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(this->MoveWorldAction, ETriggerEvent::Triggered,  this, &AGodHand::MoveWorld);
	}
	
}

void AGodHand::MoveWorld(const FInputActionValue& Value) {
	const FVector2d CurrentValue = Value.Get<FVector2d>();
	UE_LOG(LogTemp, Log, TEXT("Moving FUnction with the following Paramters: %s"), *CurrentValue.ToString());
}

