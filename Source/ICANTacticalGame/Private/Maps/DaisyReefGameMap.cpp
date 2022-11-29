// Fill out your copyright notice in the Description page of Project Settings.

#include "Maps/DaisyReefGameMap.h"

#include "Actors/DaisyReefMapElement.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/Maps/DaisyReefMapObject.h"

// Sets default values
ADaisyReefGameMap::ADaisyReefGameMap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ADaisyReefGameMap::BeginPlay()
{
	
}
