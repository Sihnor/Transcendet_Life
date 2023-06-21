// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Transcendet_Life/Characters/Professions/Profession.h"
#include "Lumberjack.generated.h"


UCLASS()
class TRANSCENDET_LIFE_API ALumberjack : public AProfession {
  GENERATED_BODY()

public:
  // Sets default values for this character's properties
  ALumberjack();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

private:
  // Called every frame
  virtual void Tick(float DeltaTime) override;
  
public:
  /** Bool for AnimBP to switch to another animation set */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
  bool bHasAxe;

  /** Setter to set the bool */
  UFUNCTION(BlueprintCallable, Category = Weapon)
  void SetHasAxe(bool bNewHasAxe);

  /** Getter for the bool */
  UFUNCTION(BlueprintCallable, Category = Weapon)
  bool GetHasAxe() const;

protected:
  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
  
};
