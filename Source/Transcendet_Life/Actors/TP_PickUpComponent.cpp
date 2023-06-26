// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_PickUpComponent.h"
#include "Transcendet_Life/Characters/Professions/Profession.h"


// Sets default values for this component's properties
UTP_PickUpComponent::UTP_PickUpComponent()
{
  // Setup Sphere Collision
  this->SphereRadius = 32.0f;
}


// Called when the game starts
void UTP_PickUpComponent::BeginPlay()
{
  Super::BeginPlay();

  // Register our Overlap Event
  this->OnComponentBeginOverlap.AddDynamic(this, &UTP_PickUpComponent::OnSphereBeginOverlap);
}

void UTP_PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

  // Checking if a Profession Character is overlapping
  AProfession* Character = Cast<AProfession>(OtherActor);
  if (Character != nullptr) {
    // Notify that the actor is being picked up
    this->OnPickUp.Broadcast(Character);

    // Unregister from the Overlap Event so it is no longer triggered
    this->OnComponentBeginOverlap.RemoveAll(this);
  }
  
}


