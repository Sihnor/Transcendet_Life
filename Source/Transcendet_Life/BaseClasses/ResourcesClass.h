// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourcesClass.generated.h"

UCLASS()
class TRANSCENDET_LIFE_API AResourcesClass : public AActor {
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  AResourcesClass();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  //////////////////////////////////////////////////////////////////////////// Components
  ///
  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
  class USceneComponent* Root;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
  class UStaticMeshComponent* ResourcesMesh;
};
