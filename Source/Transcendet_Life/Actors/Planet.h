// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Planet.generated.h"

class AGravityCharacter;
class URectLightComponent;
class USphereComponent;

// Declaration of the delegate that will be called when there is a new Actor is spawning
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpawn, AActor*, GravityActor);

UCLASS()
class TRANSCENDET_LIFE_API APlanet : public AActor {
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable, Category="Gravity")
  FOnSpawn EventOnSpawn;
  
  // Sets default values for this actor's properties
  APlanet();

  virtual void Tick(float DeltaSeconds) override;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  USphereComponent* Center;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  UStaticMeshComponent* WorldMesh;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  USphereComponent* GravityField;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  URectLightComponent* NorthLight;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  URectLightComponent* SouthLight;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  URectLightComponent* EastLight;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  URectLightComponent* WestLight;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  URectLightComponent* FrontLight;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  URectLightComponent* BackLight;

  
protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

private:

  // An Array of Actors that will be affected
  UPROPERTY()
  TArray<AGravityCharacter*> CharactersAffectedOnGravity;

 

};
