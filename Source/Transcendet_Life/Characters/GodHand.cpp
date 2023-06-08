// Fill out your copyright notice in the Description page of Project Settings.



#include "GodHand.h"

#include <Components/StaticMeshComponent.h>


// Sets default values
AGodHand::AGodHand() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup component hierarchy
	this->PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	RootComponent = PlayerMesh;
	this->PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	this->PlayerCamera->SetupAttachment(this->PlayerMesh);
}

// Called when the game starts or when spawned
void AGodHand::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void AGodHand::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGodHand::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
}

