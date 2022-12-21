// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/DaisyReefPawnClasses.h"


// Sets default values for this component's properties
UDaisyReefPawnClasses::UDaisyReefPawnClasses()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UDaisyReefPawnClasses::SetPawnTeam(UDaisyReefTeamObject* NewTeam)
{
	PawnTeam = NewTeam;
}

UDaisyReefTeamObject* UDaisyReefPawnClasses::GetPawnTeam()
{
	return PawnTeam;
}

bool UDaisyReefPawnClasses::PawnHasTeam()
{
	return PawnTeam != nullptr && PawnTeam->IsValidLowLevel();
}


// Called when the game starts
void UDaisyReefPawnClasses::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

