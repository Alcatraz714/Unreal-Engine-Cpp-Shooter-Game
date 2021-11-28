// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "AmmoType.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_SubmachineGun UMETA(DisplayName = "SubmachineGun"),
	EWT_AssaultRifle UMETA(DisplayName = "AssaultRifle"),

	EWT_MAX UMETA(DisplayName = "DefaultMax")
};

/**
 * 
 */
UCLASS()
class SHOOTER_API AWeapon : public AItem
{
	GENERATED_BODY()

public:
	AWeapon();

	virtual void Tick(float DeltaTime) override;

protected:

	void StopFalling();

private:

	FTimerHandle ThrowWeaponTimer;
	float ThrowWeaponTime;
	bool bFalling;

	// When reloading the clip is moving - true
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WeaponProperties", meta = (AllowPrivateAccess = "true"))
	bool bMovingClip;

	// Ammo count for this Weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponProperties", meta = (AllowPrivateAccess = "true"))
	int32 Ammo;

	// Magzine Cap for this weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponProperties", meta = (AllowPrivateAccess = "true"))
	int32 MagazineCapacity;

	// Weapon type variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponProperties", meta = (AllowPrivateAccess = "true"))
	EWeaponType WeaponType;

	// EAmmoType - for this weapon 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponProperties", meta = (AllowPrivateAccess = "true"))
	EAmmoType AmmoType;

	// Weapon type reload montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponProperties", meta = (AllowPrivateAccess = "true"))
	FName ReloadMontageSection;

	// Clip bone name for weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponProperties", meta = (AllowPrivateAccess = "true"))
	FName ClipBoneName;

public:

	// Public - add an impulse on weapon
	void ThrowWeapon();
	// Getter for Ammo count
	FORCEINLINE int32 GetAmmo() const { return Ammo; }
	// Getter for Mag Capacity
	FORCEINLINE int32 GetMagazineCapacity() const { return MagazineCapacity; }
	// Decrement Ammo call from Character Class
	void DecrementAmmo();
	// Getter for Weapon Type
	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }
	// Getter for ammo type
	FORCEINLINE EAmmoType GetAmmoType() const { return AmmoType; }
	// Getter for montage section
	FORCEINLINE FName GetReloadMontageSection() const { return ReloadMontageSection; }
	// reload Ammo
	void ReloadAmmo(int32 Amount);
	// Getter for Clip Bone Name
	FORCEINLINE FName GetClipBoneName() const { return ClipBoneName; }
	// Setter for ClipMoving
	FORCEINLINE void SetMovingClip(bool Move) { bMovingClip = Move; }
	// Getter for Max Clip for reload only when below max clip size
	bool ClipIsFull();
};
