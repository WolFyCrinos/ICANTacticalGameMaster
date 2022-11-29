// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DaisyReefMapElement.h"

// Sets default values
ADaisyReefMapElement::ADaisyReefMapElement()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADaisyReefMapElement::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADaisyReefMapElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
