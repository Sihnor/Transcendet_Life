// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GodHand.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;

UCLASS()
class TRANSCENDET_LIFE_API AGodHand : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGodHand();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Adding the Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* MoveWorldAction;

	void MoveWorld(const FInputActionValue& Value);
	
private:
	/**
	 * @brief Mesh of the player being dispayed
	 */
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PlayerMesh;

	
	
	/**
	 * @brief Camera to view the scene
	 */
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* PlayerCamera;
};
