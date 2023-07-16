// Fill out your copyright notice in the Description page of Project Settings.


#include "GodController.h"

AGodController::AGodController() {
  this->GodPlayer = nullptr;
  this->SelectedCharacter = nullptr;
}

void AGodController::OnPossess(APawn* InPawn) {
  Super::OnPossess(InPawn);

  UE_LOG(LogTemp, Warning, TEXT("ES WIRD EINMAL GEWESEN SEIN"))
}



