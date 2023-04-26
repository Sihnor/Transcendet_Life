// Copyright Epic Games, Inc. All Rights Reserved.


#include "Transcendet_LifeGameModeBase.h"

#include "GameFramework/DefaultPawn.h"
#include "Transcendet_Life/Characters/GodHand.h"


void ATranscendet_LifeGameModeBase::InitGameState() {
	Super::InitGameState();

	// Check if no hard override is active
	if (DefaultPawnClass == ADefaultPawn::StaticClass()) {
		// Update to custom implementation
		DefaultPawnClass = this->CustomPawnClass;
	}
}
