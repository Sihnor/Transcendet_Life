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


// On Click Event
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClick, FKey, ButtonClicked);

// Gravity character class which overrides gravity movement component
UCLASS()
class TRANSCENDET_LIFE_API AGravityCharacter : public APawn {
  GENERATED_BODY()

public:
  // Sets default values for this character's properties
  AGravityCharacter();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

private:
  //////////////////////////////////////////////////////////////////////////// Input Mapping Context

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

  /** Look Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  UInputAction* PossesAction;

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

  // Called to un possess
  void UnPosses(const FInputActionValue& Value);

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
  //////////////////////////////////////////////////////////////////////////// For possessing
  void PreparePosses(class AGodHand* God);
  

public:
  //////////////////////////////////////////////////////////////////////////// Events
  ///
  UPROPERTY(BlueprintAssignable, Category="EventDospatcher")
  FOnClick EventOnClick;

public:
  //////////////////////////////////////////////////////////////////////////// Components
  ///
  /** The CapsuleComponent being used for movement collision (by CharacterMovement). Always treated as being vertically aligned in simple collision check functions. */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Character, meta=(AllowPrivateAccess = "true"))
  TObjectPtr<UCapsuleComponent> CapsuleComponent;

  /** The main skeletal mesh associated with this Character (optional sub-object). */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Character, meta=(AllowPrivateAccess = "true"))
  USkeletalMeshComponent* CharacterMesh;

  /** Component shown in the editor only to indicate character facing */
  UPROPERTY()
  UArrowComponent* ArrowComponent;

  /** Camera boom positioning the camera behind the character */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Camera, meta = (AllowPrivateAccess = "true"))
  USpringArmComponent* SpringArm;

  /** Camera boom positioning the camera behind the character */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Camera, meta = (AllowPrivateAccess = "true"))
  UCameraComponent* CameraComponent;

  /** Movement component used for movement logic in various movement modes (walking, falling, etc), containing relevant settings and functions to control movement. */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Character, meta=(AllowPrivateAccess = "true"))
  class UGravityMovementComponent* CharacterMovement;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Character, meta=(AllowPrivateAccess = "true"))
  class UWidgetComponent* CharacterHUD;
  
public:
  //////////////////////////////////////////////////////////////////////////// Getter and Setter
  ///
  /** Returns CapsuleComponent sub object **/
  FORCEINLINE class UCapsuleComponent* GetCapsuleComponent() const { return CapsuleComponent; }

  /** Returns Mesh sub object **/
  FORCEINLINE class USkeletalMeshComponent* GetCharacterMesh() const { return this->CharacterMesh; }

  /** Returns Camera sub object **/
  FORCEINLINE class UCameraComponent* GetCamera() const { return this->CameraComponent; }

  // Get the GravityComponent
  UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character")
  UGravityMovementComponent* GetGravityMovementComponent();

public:
  class AGodHand* GodHand;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  bool bCanBePossessed;

};
