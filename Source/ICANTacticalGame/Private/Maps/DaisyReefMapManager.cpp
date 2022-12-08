// Fill out your copyright notice in the Description page of Project Settings.

#include "Maps/DaisyReefMapManager.h"

#include "Kismet/GameplayStatics.h"
#include "Maps/DaisyReefMapGenerator.h"

// Sets default values
ADaisyReefMapManager::ADaisyReefMapManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ADaisyReefMapManager::BeginPlay()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient; // We never want to save player controllers into a map
	SpawnInfo.bDeferConstruction = true;

	if (MapGeneratorClass != nullptr)
	{
		MapGenerator = GetWorld()->SpawnActor<ADaisyReefMapGenerator>(MapGeneratorClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);

		UGameplayStatics::FinishSpawningActor(MapGenerator,FTransform(FRotator::ZeroRotator,  FVector::ZeroVector));
		
		for (auto Element : MapGenerator->BeginGenerate())
		{
			if (Element->GetIsWalkable())
			{
				FloorMapElementsSpawned.AddUnique(Element);
			}
			else
			{
				WallMapElementsSpawned.AddUnique(Element);
			}
		}
	}
}
