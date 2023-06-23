// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "TP_PickUpComponent.generated.h"

// Declaration of the delegate that will be called when someone picks this up
// The character picking this up is the parameter sent with the notification
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUp, AProfession*, PickUpCharacter);

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRANSCENDET_LIFE_API UTP_PickUpComponent : public USphereComponent
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable, Category="Interaction")
  FOnPickUp OnPickUp;
  
  // Sets default values for this component's properties
  UTP_PickUpComponent();

protected:
  // Called when the game starts
  virtual void BeginPlay() override;

  // Code for when something overlaps this component
  UFUNCTION()
  void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};