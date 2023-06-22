// Fill out your copyright notice in the Description page of Project Settings.


#include "Planet.h"

#include "Components/RectLightComponent.h"
#include "Components/SphereComponent.h"
#include "Math/TransformCalculus3D.h"
#include "Transcendet_Life/Characters/Professions/Profession.h"


// Sets default values
APlanet::APlanet() {

  constexpr int WorldScale = 5.0f;

  this->Center = CreateDefaultSubobject<USphereComponent>(TEXT("Center"));
  this->Center->SetWorldScale3D(FVector(WorldScale));
  this->SetRootComponent(this->Center);
  this->Center->SetSphereRadius(32.0);

  this->WorldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanetMesh"));
  this->WorldMesh->SetRelativeScale3D(FVector(1.0f));
  this->WorldMesh->SetupAttachment(this->Center);

  this->GravityField = CreateDefaultSubobject<USphereComponent>(TEXT("GravityField"));
  this->GravityField->SetRelativeScale3D(FVector(1.0f));
  this->GravityField->SetupAttachment(this->WorldMesh);
  this->GravityField->SetSphereRadius(150.0);

  this->NorthLight = CreateDefaultSubobject<URectLightComponent>(TEXT("NorthLight"));
  this->NorthLight->SetRelativeLocation(FVector(0.0f, 0.0f, this->GravityField->GetScaledSphereRadius() + WorldScale * 10));
  this->NorthLight->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
  this->NorthLight->SetAttenuationRadius(this->NorthLight->AttenuationRadius * WorldScale);
  this->NorthLight->SetupAttachment(this->Center);
  this->SouthLight = CreateDefaultSubobject<URectLightComponent>(TEXT("SouthLight"));
  this->SouthLight->SetRelativeLocation(FVector(0.0f, 0.0f, (this->GravityField->GetScaledSphereRadius() + WorldScale * 10) * -1));
  this->SouthLight->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
  this->SouthLight->SetAttenuationRadius(this->NorthLight->AttenuationRadius * WorldScale);
  this->SouthLight->SetupAttachment(this->Center);
  this->EastLight = CreateDefaultSubobject<URectLightComponent>(TEXT("EastLight"));
  this->EastLight->SetRelativeLocation(FVector(0.0f, this->GravityField->GetScaledSphereRadius() + WorldScale * 10, 0.0f));
  this->EastLight->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
  this->EastLight->SetAttenuationRadius(this->NorthLight->AttenuationRadius * WorldScale);
  this->EastLight->SetupAttachment(this->Center);
  this->WestLight = CreateDefaultSubobject<URectLightComponent>(TEXT("WestLight"));
  this->WestLight->SetRelativeLocation(FVector(0.0f, (this->GravityField->GetScaledSphereRadius() + WorldScale * 10) * -1, 0.0f));
  this->WestLight->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
  this->WestLight->SetAttenuationRadius(this->NorthLight->AttenuationRadius * WorldScale);
  this->WestLight->SetupAttachment(this->Center);
  this->FrontLight = CreateDefaultSubobject<URectLightComponent>(TEXT("FrontLight"));
  this->FrontLight->SetRelativeLocation(FVector(this->GravityField->GetScaledSphereRadius() + WorldScale * 10, 0.0f, 0.0f));
  this->FrontLight->SetRelativeRotation(FRotator(180.0f, 0.0f, 0.0f));
  this->FrontLight->SetAttenuationRadius(this->NorthLight->AttenuationRadius * WorldScale);
  this->FrontLight->SetupAttachment(this->Center);
  this->BackLight = CreateDefaultSubobject<URectLightComponent>(TEXT("BackLight"));
  this->BackLight->SetRelativeLocation(FVector((this->GravityField->GetScaledSphereRadius() + WorldScale * 10) * -1, 0.0f, 0.0f));
  this->BackLight->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
  this->BackLight->SetAttenuationRadius(this->NorthLight->AttenuationRadius * WorldScale);
  this->BackLight->SetupAttachment(this->Center);
}

// Called when the game starts or when spawned
void APlanet::BeginPlay() {
  Super::BeginPlay();

  
  //this->GravityField->IsOverlappingActor()
  
}





