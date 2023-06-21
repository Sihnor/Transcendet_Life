// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp_Tool.h"

#include "TP_PickUpComponent.h"


// Sets default values
APickUp_Tool::APickUp_Tool() {

  // Setup the hierarchy
  this->TP_Tool   = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TP_Weapon"));
  this->SetRootComponent(this->TP_Tool);

  this->TP_PickUp = CreateDefaultSubobject<UTP_PickUpComponent>(TEXT("TP_PickUp"));
  this->TP_PickUp->SetupAttachment(this->TP_Tool);

  this->ToolMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AxeMesh"));
  this->ToolMesh->SetupAttachment(this->TP_PickUp);
  
  
}

// Called when the game starts or when spawned
void APickUp_Tool::BeginPlay() {
  Super::BeginPlay();
  
}



