// Fill out your copyright notice in the Description page of Project Settings.


#include "Profession.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AProfession::AProfession()  {
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  // Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
  this->Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
  this->Mesh1P->SetOnlyOwnerSee(true);
  this->Mesh1P->SetupAttachment(this->GetCamera());
  this->Mesh1P->bCastDynamicShadow = false;
  this->Mesh1P->CastShadow = false;
  this->Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

// Called when the game starts or when spawned
void AProfession::BeginPlay() {
  Super::BeginPlay();

  

  //UCharacterMovementComponent* CharacterMovementComponent = this->GetCharacterMovement();
  //CharacterMovementComponent->SetPlaneConstraintNormal(FVector(0.0,0.0,1.0));
  
}

// Called every frame
void AProfession::Tick(const float DeltaTime) {
  Super::Tick(DeltaTime);
}

void AProfession::SetHasTool(const bool bHasNewTool) {
  this->bHasTool = bHasNewTool;
}

bool AProfession::GetHasTool() const {
  return this->bHasTool;
}
