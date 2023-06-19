// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Lumberjack.generated.h"


UCLASS()
class TRANSCENDET_LIFE_API ALumberjack : public ACharacter {
  GENERATED_BODY()

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
  bool GetHasAxe();

protected:
  /** Called for the Move Input */
  void Move(const struct FInputActionValue& Value);

  /** Called for the Look Input */
  void Look(const struct FInputActionValue& Value);

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
