// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourcesClass.h"


// Sets default values
AResourcesClass::AResourcesClass() {
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  this->Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
  this->SetRootComponent(this->Root);
  
  this->ResourcesMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
  this->ResourcesMesh->SetupAttachment(this->Root);
}

// Called when the game starts or when spawned
void AResourcesClass::BeginPlay() {
  Super::BeginPlay();
  
}

// Called every frame
void AResourcesClass::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);
}

