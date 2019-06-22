// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AnActor.generated.h"

UCLASS()
class SHIELDSUP_API AAnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnActor();

	UPROPERTY(EditAnywhere, Category = "Damage")
	//Total damage taken by the actor
	float totalDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	//Elemental damage
	float elementalDamage;  
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "Damage")
	float physicalDamage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void PostInitProperties();
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void CalculatePhysicalDamage();
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

private:
	void SetInitDamageValues();
};
