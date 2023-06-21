// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_ToolComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Transcendet_Life/Characters/Professions/Lumberjack/Lumberjack.h"


// Sets default values for this component's properties
UTP_ToolComponent::UTP_ToolComponent() {
  // Default offset from the character location for projectiles to spawn
  MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}


// Called when the game starts
void UTP_ToolComponent::BeginPlay()
{
  Super::BeginPlay();

  // ...
  
}

void UTP_ToolComponent::AttachTool(ALumberjack* TargetCharacter) {
  this->Character = TargetCharacter;
  if (this->Character != nullptr) {
    return;
  }

  // Attach the weapon to the first person Character
  const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
  AttachToComponent(this->Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

  // switch bHasAxe for the character
  this->Character->SetHasAxe(true);

  // Setup action binding
  if (const APlayerController* PlayerController = Cast<APlayerController>(this->Character->GetController()))
    {
    // Add the MappingContext with a higher priority
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
      Subsystem->AddMappingContext(UtilizeMappingContext, 1);
    }

    // Bind the Action
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent)) {
      EnhancedInputComponent->BindAction(IA_UtilizeAction, ETriggerEvent::Triggered, this, &UTP_ToolComponent::Use);
    }
  }
  
  
}

void UTP_ToolComponent::Use()
{
  if (this->Character == nullptr || this->Character->GetController() == nullptr)
  {
    return;
  }

  UE_LOG(LogTemp, Error, TEXT("The axe is currently used"));
}

void UTP_ToolComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
  if (this->Character == nullptr)
  {
    return;
  }

  if (const APlayerController* PlayerController = Cast<APlayerController>(this->Character->GetController()))
  {
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
    {
      Subsystem->RemoveMappingContext(UtilizeMappingContext);
    }
  }
  
}

