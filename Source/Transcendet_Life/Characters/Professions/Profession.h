// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Transcendet_Life/BaseClasses/GravityCharacter.h"
#include "Profession.generated.h"

UENUM(BlueprintType)
enum class EAvailableTools : uint8 {
  Axe UMETA(DisplayName = "Axe")
};


UCLASS()
class TRANSCENDET_LIFE_API AProfession : public AGravityCharacter {
  GENERATED_BODY()

public:
  // Sets default values for this character's properties
  AProfession();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  // Preferential tool for every profession
  UPROPERTY(BlueprintReadOnly)
  EAvailableTools PreferentialTool;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

private:
  //////////////////////////////////////////////////////////////////////////// Input

  // Adding the Mapping Context
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  class UInputMappingContext* DefaultMappingContext;

  /** Move Action for the world */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  class UInputAction* MoveCharacterAction;

  /** Jump Action for the world */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  class UInputAction* JumpCharacterAction;

  /** Look Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  class UInputAction* LookCharacterAction;

  //////////////////////////////////////////////////////////////////////////// Components

  /** Pawn mesh: 1st person view (arms; seen only by self) */
  UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
  class USkeletalMeshComponent* Mesh1P;

  /** First person camera */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
  class UCameraComponent* FirstPersonCameraComponent;

public:
  // Variable if the Character has a tool
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Tool)
  bool bHasTool;

  // Setter to set the bool
  UFUNCTION(BlueprintCallable, Category = Weapon)
  void SetHasTool(const bool bHasNewTool);

  // Getter for the bool 
  UFUNCTION(BlueprintCallable, Category = Weapon)
  bool GetHasTool() const;

protected:
  /** Called for the Move Input */
  void Move(const struct FInputActionValue& Value);

  /** Called for the Look Input */
  void Look(const struct FInputActionValue& Value);

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
  // Getter function for the FP Mesh
  USkeletalMeshComponent* GetMesh1P() const { return this->Mesh1P; }
  // Getter function for the Camera Component
  UCameraComponent* GetFirstPersonCameraComponent() const { return this->FirstPersonCameraComponent; }
};
