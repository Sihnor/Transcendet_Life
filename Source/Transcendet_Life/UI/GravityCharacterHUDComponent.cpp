// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityCharacterHUDComponent.h"
#include "GravityCharacterHUDMenu.h"


// Sets default values for this component's properties
UGravityCharacterHUDComponent::UGravityCharacterHUDComponent() {
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = true;

  // ...

  
}


// Called when the game starts
void UGravityCharacterHUDComponent::BeginPlay() {
  Super::BeginPlay();

  // ...
  
}


// Called every frame
void UGravityCharacterHUDComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  // ...
}

void UGravityCharacterHUDComponent::SetOwningCharacter(AGravityCharacter* Character) {
  if (this->CharacterMenu) {
    UGravityCharacterHUDMenu* TempWidget = Cast<UGravityCharacterHUDMenu>(this->CharacterMenu);
    if (TempWidget) {
      TempWidget->SetOwningCharacter(Character);
    }
  }
}

