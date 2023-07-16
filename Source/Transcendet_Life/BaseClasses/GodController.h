// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GodController.generated.h"

/**
 * 
 */
UCLASS()
class TRANSCENDET_LIFE_API AGodController : public APlayerController
{
	GENERATED_BODY()
public:
	
	AGodController();
	
	class AGodHand* GodPlayer;

	class AGravityCharacter* SelectedCharacter;

	virtual void OnPossess(APawn* InPawn) override;
	

};
