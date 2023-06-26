// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"

#include "GravityPlanet.generated.h"

class AGravityCharacter;
class URectLightComponent;
class USphereComponent;

// Declaration of the delegate that will be called when there is a new Actor is spawning
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpawn, AActor*, GravityActor);

UCLASS()
class TRANSCENDET_LIFE_API AGravityPlanet : public AStaticMeshActor {
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable, Category="Gravity")
  FOnSpawn EventOnSpawn;
  
  // Sets default values for this actor's properties
  AGravityPlanet();

  virtual void Tick(float DeltaSeconds) override;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  USphereComponent* GravityField;

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

private:
  // An Array of Actors that will be affected
  UPROPERTY()
  TArray<AGravityCharacter*> CharactersAffectedOnGravity;


private:
  float Gravitation = -1.0f;

};
