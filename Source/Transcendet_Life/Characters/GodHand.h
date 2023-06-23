// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GodHand.generated.h"


class APlanet;
class URectLightComponent;
class AStaticMeshActor;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;



UCLASS()
class TRANSCENDET_LIFE_API AGodHand : public APawn
{
	GENERATED_BODY()

protected:
	// Adding the Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MappingContext;

	/**
	 * @brief Move Action for the world 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveWorldAction;

	/**
	 * @brief The Pointer for the Object what will be Rotated
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	APlanet* RotatingObject;
	
	/**
	 * @brief The Rotation Speed for the world
	 */
	float RotationObjectSpeed = 50.0f;

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PlayerCamera;
	
public:
	// Sets default values for this pawn's properties
	AGodHand();

protected:
	/** Called for the MoveWorld Input */
	void MoveWorld(const FInputActionValue& Value);

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * @brief The Root for the Character
	 */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	USceneComponent* Root;
	
	/**
	 * @brief Mesh of the GodHand being dispayed
	 */
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* PlayerMesh;

private:
	/**
	 * @brief this function is called in the BeginPLay to get The Low Poly World to rotate later.
	 */
	void GetRotatingWorldFormAllActors();




};
