// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GravityCharacterHUDComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRANSCENDET_LIFE_API UGravityCharacterHUDComponent : public UWidgetComponent {
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  UGravityCharacterHUDComponent();

protected:
  // Called when the game starts
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

  UPROPERTY()
  TSubclassOf<class UGravityCharacterHUDMenu> CharacterMenu;

  void SetOwningCharacter(class AGravityCharacter* Character);
};
