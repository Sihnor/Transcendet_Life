// Copyright 2019 Tefel. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GravityCharacter.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;
class UArrowComponent;
class UCapsuleComponent;
class UFloatingPawnMovement;


// Gravity character class which overrides gravity movement component
UCLASS()
class TRANSCENDET_LIFE_API AGravityCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGravityCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//////////////////////////////////////////////////////////////////////////// Input

	// Adding the Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Move Action for the world */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveCharacterAction;

	/** Jump Action for the world */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpCharacterAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookCharacterAction;


protected:
	//////////////////////////////////////////////////////////////////////////// Input functions
	///
	/** Called for the Move Input */
	void Move(const FInputActionValue& Value);

	/** Called for the Look Input */
	void Look(const FInputActionValue& Value);

	/** Called for the Move Input */
	void Jump(const FInputActionValue& Value);

	/** Called for the Look Input */
	void StopJumping(const FInputActionValue& Value);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


public:
	//////////////////////////////////////////////////////////////////////////// Components

	/** The CapsuleComponent being used for movement collision (by CharacterMovement). Always treated as being vertically aligned in simple collision check functions. */
	UPROPERTY(EditAnywhere , BlueprintReadWrite, Category=Character, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	
	/** The main skeletal mesh associated with this Character (optional sub-object). */
	UPROPERTY(EditAnywhere , BlueprintReadWrite, Category=Character, meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent* CharacterMesh;

	/** Component shown in the editor only to indicate character facing */
	UPROPERTY()
	UArrowComponent* ArrowComponent;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(EditAnywhere , BlueprintReadWrite, Category=Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(EditAnywhere , BlueprintReadWrite, Category=Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;
	
	/** Movement component used for movement logic in various movement modes (walking, falling, etc), containing relevant settings and functions to control movement. */
	UPROPERTY(EditAnywhere , BlueprintReadWrite, Category=Character, meta=(AllowPrivateAccess = "true"))
	class UGravityMovementComponent* CharacterMovement;

	// Adding the process for the outline
	UPROPERTY(EditAnywhere , BlueprintReadWrite, Category=Character, meta=(AllowPrivateAccess = "true"))
	class UPostProcessComponent* Outliner;

public:
	/** Returns CapsuleComponent subobject **/
	FORCEINLINE class UCapsuleComponent* GetCapsuleComponent() const { return CapsuleComponent; }

	/** Returns Mesh subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetCharacterMesh() const { return this->CharacterMesh; }
	
	/** Returns Camera subobject **/
	FORCEINLINE class UCameraComponent* GetCamera() const { return this->CameraComponent; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character")
	UGravityMovementComponent* GetGravityMovementComponent();

	

};