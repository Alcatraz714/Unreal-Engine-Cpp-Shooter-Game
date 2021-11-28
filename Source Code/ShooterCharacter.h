// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AmmoType.h"
#include "ShooterCharacter.generated.h"

UENUM(BlueprintType)
enum class ECombatState : uint8
{
	ECS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	ECS_FireTimerInProgress UMETA(DisplayName = "FireTimerInProgress"),
	ECS_Reloading UMETA(DisplayName = "Reloading"),

	ECS_MAX UMETA(DisplayName = "DefaultMAX")
};

UCLASS()
class SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Movement - Forward/Backward
	void MoveForward(float Value);

	//Movement - Right/Left
	void MoveRight(float Value);

	/**
	* Calles via input to trun at rate
	* param - rate, 1 = 100% 
	*/
	void TurnAtRate(float Rate);
	/**
	* Calles via input to look up/down at rate
	* @param - rate, 1 = 100%
	*/
	void LookUpAtRate(float Rate);
	/**
	* Control rotation based on Mouse X movement
	* @param - value, 1 = 100%
	*/
	void Turn(float Value);
	/**
	* Control rotation based on Mouse Y movement
	* @param - value, 1 = 100%
	*/
	void LookUp(float Value);

	// Fire button pressed function
	void FireWeapon();

	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation, FVector& OutBeamLocation);

	// aiming functions 
	void AimingButtonPressed();
	void AimingButtonReleased();

	//Zooming in/ out interp 
	void CameraInterpZoom(float DeltaTime);

	//Set Rates Function based on aiming
	void SetLookRates();

	//Crosshair Spread Calculator function 
	void CalculateCrosshairSpread(float DeltaTime);

	//Ftimer Bullet fire
	void StartCrosshairBulletFire();
	
	void FinishCrosshairBulletFire();

	//Fire button press and release 
	void FireButtonPressed();
	void FireButtonReleased();

	void StartFireTimer();

	UFUNCTION()
	void AutoFireReset();

	// Pickup widget trace - line trace
	bool TraceUnderCrosshairs(FHitResult& OutHitResult, FVector& OutHitLocation);

	//Trace for Items if count items overlap>0
	void TraceForItems();

	// Spawn Default Weapon
	class AWeapon* SpawnDefaultWeapon();

	// Equip Weapon - attach to mesh any weapon
	void EquipWeapon(AWeapon* WeaponToEquip);

	// Drop Weapon - Detach and throw on the ground 
	void DropWeapon();

	// Item Select or anything - interaction
	void SelectButtonPressed();
	void SelectButtonReleased();

	// Swap Weapon - drop current and equip new item - traced
	void SwapWeapon(AWeapon* WeaponToSwap);

	// Map function for ammo and count
	void InitializeAmmoMap();

	// Check to make sure Weapon has Ammo
	bool WeaponHasAmmo();

	// Fire Weapon Functions - Improved - segregated
	void PlayFireSound();
	void SendBullet();
	void PlayGunfireMontage();

	// Reload Button Action mapping function
	void ReloadButtonPressed();

	// Reload Weapon Function
	void ReloadWeapon();

	// Check if we have ammo for given weapon type 
	bool CarryingAmmo();

	// Grab Clip - reload 1
	UFUNCTION(BlueprintCallable)
	void GrabClip();

	// Replace Clip - reload 2
	UFUNCTION(BlueprintCallable)
	void ReleaseClip();

	// Crouch button pressed binding
	void CrouchButtonPressed();

	// Jump - override for better functionality
	virtual void Jump() override;

	// Half Height changer - interp 
	void InterpCapsuleHalfHeight(float DeltaTime);

	// Refactor Aiming and Stop Aiming 
	void Aim();
	void StopAiming();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//camera boom pointer
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	//follow camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	//Base turn rate in Degrees/second
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;
	//Base look-up/down rate in Degrees/second
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;

	// Controller -
	//Hip Turn Rate
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float HipTurnRate;
	//Hip Look up Rate
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float HipLookUpRate;
	//Aiming Turn Rate
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float AimingTurnRate;
	//Aiming Look up Rate
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float AimingLookUpRate;

	// Mouse -
	//Mouse Hip scale senstivity
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseHipTurnRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseHipLookUpRate;
	
	//Mouse Aiming scale senstivity
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseAimingTurnRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseAimingLookUpRate;

	// shooting sounds 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class USoundCue* FireSound;

	// muzzle flash particles
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* MuzzleFlash;
	// hip fire montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* HipFireMontage;

	// hit particle spawn upon impact
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* ImpactParticles;

	// Smoke Trails for bullets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* BeamParticles;

	//aim bool
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool bAiming;

	// default FOV value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float CameraDefaultFOV;

	// Zoomed FOV
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float CameraZoomedFOV;

	// current FOV for this frame
	float CameraCurrentFOV;

	// Zoom interp Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float ZoomInterpSpeed;

	// spread multiplier 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crosshairs", meta = (AllowPrivateAccess = "true"))
	float CrosshairSpreadMultiplier;

	//scale factors for spread - velocity, in air, aim, shooting 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crosshairs", meta = (AllowPrivateAccess = "true"))
	float CrosshairVelocityFactor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crosshairs", meta = (AllowPrivateAccess = "true"))
	float CrosshairInAirFactor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crosshairs", meta = (AllowPrivateAccess = "true"))
	float CrosshairAimFactor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crosshairs", meta = (AllowPrivateAccess = "true"))
	float CrosshairShootingFactor;

	//duration of shoot time
	float ShootTimeDuration;
	bool bFiringBullet;
	//timer handle 
	FTimerHandle CrosshairShootTimer;

	//Action mapping pressed for shooting 
	bool bFireButtonPressed;
	//Can we Fire ? 
	bool bShouldFire;
	//Rate of Firing
	float AutomaticFireRate;
	//Timer Handle for gunshots
	FTimerHandle AutoFireTimer;

	// True if trace every frame
	bool bShouldTraceForItems;

	// Number of overlapped AItems
	int8 OverlappedItemCount;

	// Item we hit last Frame
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items", meta = (AllowPrivateAccess = "true"))
	class AItem* TraceHitItemLastFrame;

	// Current Weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	AWeapon* EquippedWeapon;

	// Default Weapon - BP weapon class
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeapon> DefaultWeaponClass;

	// Item currently hit by trace - Trace for Items
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	AItem* TraceHitItem;

	// A and B for Camera Interp
	// Distance to move 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items", meta = (AllowPrivateAccess = "true"))
	float CameraInterpDistance;
	// Upward from the camera
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items", meta = (AllowPrivateAccess = "true"))
	float CameraInterpElevation;

	// Mapping the ammo type with the amount set
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items", meta = (AllowPrivateAccess = "true"))
	TMap<EAmmoType, int32> AmmoMap;

	// Default values - Initial no. of bullets - 9mm
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items", meta = (AllowPrivateAccess = "true"))
	int32 Starting9mmAmmo;
	// Default values - Initial no. of bullets - AR
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items", meta = (AllowPrivateAccess = "true"))
	int32 StartingARAmmo;

	// Combat State - fire or reload if unoccupied
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	ECombatState CombatState;

	// Reload Weapon - Anim variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* ReloadMontage;

	// Finish Reloading 
	UFUNCTION(BLueprintCallable)
	void FinishReloading();

	// Save Transform of the Clip Bone when grabbed 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	FTransform ClipTransform;

	// Scene Component for the reload animation
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	USceneComponent* HandSceneComponent;

	// Crouching Bool - true when crouched
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool bCrouching;

	// Movement Speed for crouch walking and normal walking
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float BaseMovementSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float CrouchMovementSpeed;

	// reduce Capsule hiegt - crouching
	float CurrentCapsuleHalfHeight;
	// Standing half height
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float StandingCapsuleHalfHeight;
	// Crouching half height
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float CrouchingCapsuleHalfHeight;

	// Ground Friction changes to allow sliding when Standing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float BaseGroundFriction;
	// Ground Friction when Crouching to prevent Sliding
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float CrouchingGroundFriction;

	// Internal C++ button press - RMB
	bool bAimnigButtonPressed;

public:
	//return subobject 
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	//return subobject camera 
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	// getter for bAiming
	FORCEINLINE bool GetAiming() const { return bAiming; }
	// return crosshair spread
	UFUNCTION(BlueprintCallable)
	float GetCrosshairSpreadMultiplier() const;

	FORCEINLINE int8 GetOverlappedItemCount() const { return OverlappedItemCount; }

	// Adds/ Subs to/from overlapped count and updates bShouldTraceForItems - scan if count != 0
	void IncrementOverlappedItemCount(int8 Amount);

	// Item Interp before adding to the inventory / equip / swap
	FVector GetCameraInterpLocation();

	// Item Pickup Type Getter 
	void GetPickupItem(AItem* Item);

	// Getter for reloading in AnimInstance.cpp
	FORCEINLINE ECombatState GetCombatState() const { return CombatState; }

	// Getter for bCrouching
	FORCEINLINE bool GetCrouching() const { return bCrouching; }

};
