// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tree.generated.h"

UCLASS()
class TRANSCENDET_LIFE_API ATree : public AActor {
  GENERATED_BODY()

private:
  // Root Component
  UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(AllowPrivateAccess="true"))
  USceneComponent* Root;
  
  // Mesh of the GodHand being dispayed
  UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = "true"))
  UStaticMeshComponent* TreeMesh;

public:
  // Sets default values for this actor's properties
  ATree();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;
};
