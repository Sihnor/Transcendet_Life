// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityPlanet.h"

#include "GravityCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AGravityPlanet::AGravityPlanet() {
  constexpr int WorldScale = 5.0f;

  this->SetRootComponent(this->GetStaticMeshComponent());

  this->GravityField = CreateDefaultSubobject<USphereComponent>(TEXT("GravityField"));
  this->GravityField->SetRelativeScale3D(FVector(1.0f));
  this->GravityField->SetupAttachment(this->GetStaticMeshComponent());
  this->GravityField->SetSphereRadius(250.0);

  
}

// Called when the game starts or when spawned
void AGravityPlanet::BeginPlay() {
  Super::BeginPlay();

  // Getting all Characters that are affected on gravity
  TArray<AActor*> FoundCharacters;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGravityCharacter::StaticClass(), FoundCharacters);
  for (AActor* Actor : FoundCharacters) {
    AGravityCharacter* Character = Cast<AGravityCharacter>(Actor);
    this->CharactersAffectedOnGravity.Add(Cast<AGravityCharacter>(Character));
    // Setting the Variable for the Planet
    Character->SetPlanetCenter(this->GetActorLocation());
    //UE_LOG(LogTemp, Warning, TEXT("X:%f Y=%f Z=%f"), this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z);
    Character->SetCharacterHasGravity(true);
    //Character->UpdateGravity();
  }
  

}

void AGravityPlanet::Tick(float DeltaSeconds) {
  for (AGravityCharacter* Character: this->CharactersAffectedOnGravity) {
    const FVector WorldLocation = this->GetActorLocation();
    const FVector CharacterLocation = Character->GetActorLocation();

    // Calculate the Vector from World Center to Character and Normalize it
    const FVector NormalizeWorldCharacterLocation = (CharacterLocation - WorldLocation).GetSafeNormal();

    // Get a vector in front of the character (From the Center of the planet to in-front of the character)
    const FVector WorldToInFrontOfCharacter = Character->GetActorForwardVector() + CharacterLocation;
    
    // Normalize the Vector with points from center of the planet to in-front of the character
    const FVector NormalizeWorldInFrontOfCharacter = (WorldToInFrontOfCharacter - WorldLocation).GetSafeNormal();
    

    // Calculate the distance from the center of the planet and the character
    const float DistanceCharacterWorld = sqrt(pow((CharacterLocation - WorldLocation).X, 2) + pow((CharacterLocation - WorldLocation).Y, 2) + pow((CharacterLocation - WorldLocation).Z, 2));
    
    // Calculate the vector from the center to in-front of the character
    const FVector DestinationCharacter = NormalizeWorldInFrontOfCharacter * DistanceCharacterWorld;
    

    //  Normalize the vektor from the character to the destination
    const FVector NormalizeCharacterToDestination = (DestinationCharacter - CharacterLocation).GetSafeNormal();
    
    // Calculate the Charater Rotation in Relation to the Looking direction and the axis from character to center
    const FRotator CharacterRotator = FRotationMatrix::MakeFromXZ(NormalizeCharacterToDestination, NormalizeWorldCharacterLocation).Rotator();
    Character->SetActorRotation(CharacterRotator);
    Character->GetMovementComponent()->AddInputVector(NormalizeWorldCharacterLocation * Gravitation);
    
  }
}
