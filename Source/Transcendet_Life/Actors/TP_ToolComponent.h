// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_ToolComponent.generated.h"


class ALumberjack;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRANSCENDET_LIFE_API UTP_ToolComponent : public USkeletalMeshComponent
{
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  UTP_ToolComponent();

protected:
  // Called when the game starts
  virtual void BeginPlay() override;

public:
  // Tool muzzle's offset from Player Location
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay")
  FVector MuzzleOffset;

  // Mapping Context
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess="true"))
  class UInputMappingContext* UtilizeMappingContext;

  // Utilize Action Input
  class UInputAction* IA_UtilizeAction;

public:
  // Attached the actor to a Lumberjack
  UFUNCTION(BlueprintCallable, Category="Tool")
  void AttachTool(ALumberjack* TargetCharacter);

  // Use the tool
  UFUNCTION(BlueprintCallable, Category="Tool")
  void Use();

protected:
  // Ends gameplay fot this component
  virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
  // The Character holding this tool
  ALumberjack* Character;
  
};

