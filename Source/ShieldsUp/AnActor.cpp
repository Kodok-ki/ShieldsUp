// Fill out your copyright notice in the Description page of Project Settings.


#include "AnActor.h"

// Sets default values
AAnActor::AAnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AAnActor::SetInitDamageValues();
}

// Called when the game starts or when spawned
void AAnActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*Called in constructor*/
void AAnActor::SetInitDamageValues()
{
	totalDamage = 200;
	elementalDamage = 84;
}

void AAnActor::PostInitProperties()
{
	Super::PostInitProperties();
	CalculatePhysicalDamage();
}

#if WITH_EDITOR
void AAnActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	CalculatePhysicalDamage();
}
#endif // WITH_EDITOR


void AAnActor::CalculatePhysicalDamage()
{
	physicalDamage = totalDamage - elementalDamage;
}

