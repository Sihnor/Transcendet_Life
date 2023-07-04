// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GodHand.generated.h"


UCLASS()
class TRANSCENDET_LIFE_API AGodHand : public APawn {
  GENERATED_BODY()

protected:
  // Adding the Mapping Context
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  class UInputMappingContext* MappingContext;

  /**
   * @brief Move Action for the world 
   */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  class UInputAction* RotatePlanetAction;

  // Input Action to zoom
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta = (AllowPrivateAccess="true"))
  class UInputAction* ZoomPlanetAction;

  // Input Action to zoom
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta = (AllowPrivateAccess="true"))
  class UInputAction* MoveHandMeshAction;

  /**
   * @brief The Pointer for the Object what will be Rotated
   */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
  class AGravityPlanet* RotatingObject;

  /**
   * @brief The Rotation Speed for the world
   */
  float RotationObjectSpeed = 50.0f;

private:
  // The Root for the Character
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
  USceneComponent* Root;

  // Mesh of the GodHand being dispayed
  UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = "true"))
  USkeletalMeshComponent* PlayerMesh;

  /** Camera boom positioning the camera behind the character */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
  class USpringArmComponent* SpringArm;

  /** Follow camera */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
  class UCameraComponent* PlayerCamera;

  // Box collision with the same dimension like the decal for the overlap event
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
  class UBoxComponent* SelectionOverlap;
  
  // Decal for the mouse position on the planet
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
  class UDecalComponent* Selection;

public:
  // Sets default values for this pawn's properties
  AGodHand();

  // Called every frame
  virtual void Tick(float DeltaTime) override;

protected:
  /** Called for the MoveWorld Input */
  void RotatePlanet(const struct FInputActionValue& Value);

  // Called to zoom
  void ZoomPlanet(const struct FInputActionValue& Value);

  // Called to to Move
  void MoveCursor(const struct FInputActionValue& Value);

protected:
  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  UFUNCTION()
  void OnDecalBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Actor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
  
  UFUNCTION()
  void OnDecalEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Actor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
  bool bIsOverlapped;

private:
  /**
   * @brief this function is called in the BeginPLay to get The Low Poly World to rotate later.
   */
  void GetRotatingWorldFormAllActors();

  // Sub Function of Action MoveCursor to move the Hand Mesh
  void MoveHandMesh() const;

  // Sub Function of Action MoveCursor to move the Decal
  void MoveDecal() const;
};
