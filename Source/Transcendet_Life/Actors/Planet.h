// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Planet.generated.h"

class URectLightComponent;
class USphereComponent;

UCLASS()
class TRANSCENDET_LIFE_API APlanet : public AActor {
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  APlanet();

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

 

};
