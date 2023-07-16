// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GravityCharacterHUDMenu.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class TRANSCENDET_LIFE_API UGravityCharacterHUDMenu : public UUserWidget {
  GENERATED_BODY()

public:

  UPROPERTY(EditAnywhere, meta=(BindWidget))
  class UButton* CharacterMenu;

  UFUNCTION(BlueprintCallable)
  class AGravityCharacter* GetOwningCharacter(){return  this->OwningCharacter; };
  
  
  class AGravityCharacter* OwningCharacter;
  
  void SetOwningCharacter(class AGravityCharacter* Character);
};
