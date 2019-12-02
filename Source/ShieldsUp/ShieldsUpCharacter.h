// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "ShieldsUpCharacter.generated.h"

UCLASS(config=Game)
class AShieldsUpCharacter : public ACharacter
{
	GENERATED_BODY()

public: 
	AShieldsUpCharacter();
	AShieldsUpCharacter(const FObjectInitializer& ObjectInitializer);

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = "Shield")
	TSubclassOf<AActor> Shield;

public:

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	/** Ranges from 0 to 100**/
	float HealthPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	bool bIsAlive;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Blocking")
	bool bIsBlocking;
	
	
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blocking")
	//float ParryFrames;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPawnNoiseEmitterComponent* PawnNoiseEmitterComponent;

protected:

	virtual void BeginPlay() override;

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Called for blocking with the player's shield*/
	void OnBlock();

	/** Called for releasing player's blocking stance*/
	void ReleaseBlock();

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void GameOverHandler();

	UFUNCTION()
	void StartParryTimer();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

protected:

	UPROPERTY()
	FTimerHandle ParryTimer;

	UPROPERTY()
	FTimerHandle& ParryTimerRef = ParryTimer;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blocking")
	bool bIsParrying;

public:

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "AI")
	void ReportNoise(USoundBase* SoundToPlay, float Volume);

	UFUNCTION(BlueprintCallable, Category = "Collision")
	bool PlayerIsHitHandler(const float Damage, const class AActor* DamageCauser);

	UFUNCTION(Category = "Blocking")
	void Parry();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	virtual float TakeDamage(const float Damage, const class AActor* DamageCauser);

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE FTimerHandle GetParryTimer() const { return ParryTimer; }
	
	FORCEINLINE bool GetParryStatus() const {return bIsParrying; }
	FORCEINLINE void SetParryStatus(const bool OutStatus) { bIsParrying = OutStatus; }
};

