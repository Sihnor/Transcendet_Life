// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Transcendet_Life/Characters/GodHand.h"
#include "Transcendet_LifeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TRANSCENDET_LIFE_API ATranscendet_LifeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void InitGameState() override;

private:
	// Lock the Default Pawn to a Class or Subclass of AGodHand
	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<AGodHand> CustomPawnClass = AGodHand::StaticClass();
};
