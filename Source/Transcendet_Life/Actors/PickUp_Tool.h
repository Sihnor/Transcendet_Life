// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUp_Tool.generated.h"

class UTP_ToolComponent;
class UTP_PickUpComponent;

UCLASS()
class TRANSCENDET_LIFE_API APickUp_Tool : public AActor
{
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  APickUp_Tool();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // SkeletalMesh
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  UTP_ToolComponent* TP_Tool;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  UTP_PickUpComponent* TP_PickUp;

  // SkeletalMesh
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
  USkeletalMeshComponent* ToolMesh;

  
};
