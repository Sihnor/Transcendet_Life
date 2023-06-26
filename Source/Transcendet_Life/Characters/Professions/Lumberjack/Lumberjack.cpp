// Fill out your copyright notice in the Description page of Project Settings.


#include "Lumberjack.h"

// Sets default values
ALumberjack::ALumberjack()  {
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  // Set the preferential tool for the profession
  this->PreferentialTool = EAvailableTools::Axe;
  
  // Character doesnt have a axe at start
  this->bHasAxe = false;
  

  AutoPossessPlayer = EAutoReceiveInput::Player0;
  AutoReceiveInput = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ALumberjack::BeginPlay() {
  Super::BeginPlay();

  
}

// Called every frame
void ALumberjack::Tick(const float DeltaTime) {
  Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ALumberjack::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);
  
}


void ALumberjack::SetHasAxe(const bool bNewHasAxe) {
  this->bHasAxe = bNewHasAxe;
}

bool ALumberjack::GetHasAxe() const {
  return this->bHasAxe;
}


