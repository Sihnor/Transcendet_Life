// Fill out your copyright notice in the Description page of Project Settings.


#include "Tree.h"

#include "NavigationSystemTypes.h"


// Sets default values
ATree::ATree() {
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  this->Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootCompoennt"));
  this->SetRootComponent(this->Root);

  this->TreeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TreeMeshComponent"));
  this->TreeMesh->SetupAttachment(this->Root);
}

// Called when the game starts or when spawned
void ATree::BeginPlay() {
  Super::BeginPlay();
  
}

// Called every frame
void ATree::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);
}

