// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	EIR_Damaged UMETA(DisplayName = "Damaged"),
	EIR_Common UMETA(DisplayName = "Common"),
	EIR_Uncommon UMETA(DisplayName = "Uncommon"),
	EIR_Rare UMETA(DisplayName = "Rare"),
	EIR_Legendary UMETA(DisplayName = "Legendary"),

	EIR_MAX UMETA(DisplayName = "DefaultMax")
};

UENUM(BlueprintType)
enum class EItemState : uint8
{
	EIS_Pickup UMETA(DisplayName = "Pickup"),
	EIS_EquipInterping UMETA(DisplayName = "EquipInterping"),
	EIS_PickedUp UMETA(DisplayName = "PickedUp"),
	EIS_Equipped UMETA(DisplayName = "Equipped"),
	EIS_Falling UMETA(DisplayName = "Falling"),
	
	EIS_MAX UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class SHOOTER_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when Overlap Area Sphere
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Called when End Overlap Area Sphere
	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Sets the active stars bool value - visble / not
	void SetActiveStars();

	// Set Properties of item based on state enum
	void SetItemProperties(EItemState State);

	// call when finish timer for interp
	void FinishInterping();
	// Handles item interp when equipinterping state
	void ItemInterp(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	// Skeletal Mesh for items
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* ItemMesh;

	// Line trace collision to show pickup widgets
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	class UBoxComponent* CollisionBox;

	// Widget popup when line trace collision
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	class UWidgetComponent* PickupWidget;

	// Sphere Component for item Detection - Area Sphere
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	class USphereComponent* AreaSphere;

	// Item Name for widget
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	FString ItemName;
	
	// Item Count for specific item derived classes - eg - Bullets for guns etc 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	int32 ItemCount;

	// Rarity - number of stars
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	EItemRarity ItemRarity;

	// Active stars Tarray
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	TArray<bool> ActiveStars;

	// State - Weapon State
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	EItemState ItemState;

	// Curve path
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	class UCurveFloat* ItemZCurve;

	// Start Locaiton for the Curve 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	FVector ItemInterpStartLocation;

	// Camera Location - target 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	FVector CameraTargetLocation;

	// bool for interp
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	bool bInterping;

	// Timer Handle for Interping
	FTimerHandle ItemInterpTimer;

	// Time for curve and timer
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	float ZCurveTime;

	// ref for Shooter Character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	class AShooterCharacter* Character;

	// Variables to change the x an y comps for curve
	float ItemInterpX;
	float ItemInterpY;

	// Stop rotation of weapon while interping
	float InterpInitialYawOffset;

	// Saling curve for interping
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	UCurveFloat* ItemScaleCurve;

	// Pickup sound added when floats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	class USoundCue* PickupSound;

	// Equip - gun Sound when equipped by char
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	USoundCue* EquipSound;


public:
	// Getter and Setter Fucnitons
	FORCEINLINE UWidgetComponent* GetPickupWidget() const { return PickupWidget; }
	// Getter for Area Sphere
	FORCEINLINE USphereComponent* GetAreaSphere() const { return AreaSphere; }
	// Getter for BoxComponent
	FORCEINLINE UBoxComponent* GetCollisionBox() const { return CollisionBox; }
	// Getter for Item State
	FORCEINLINE EItemState GetItemState() const { return ItemState; }
	// Setter For Item State
	void SetItemState(EItemState State);
	// Getter for Item Mesh
	FORCEINLINE USkeletalMeshComponent* GetItemMesh() const { return ItemMesh; }
	// Item Curve Starter from character 
	void StartItemCurve(AShooterCharacter* Char);
	// Getter for Pickup Sound
	FORCEINLINE USoundCue* GetPickupSound() const { return PickupSound; }
	// Getter for Equip Sound 
	FORCEINLINE USoundCue* GetEquipSound() const { return EquipSound; }
};
