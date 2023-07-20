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

