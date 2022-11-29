// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/DaisyReefGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Maps/DaisyReefGameMap.h"

ADaisyReefGameMode::ADaisyReefGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.DoNotCreateDefaultSubobject(TEXT("Sprite")))
{
	GameMapClass = nullptr;
}


ADaisyReefGameMap* ADaisyReefGameMode::GetGameMap() const
{
	return SpawnedGameMap;
}

void ADaisyReefGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	if (GameMapClass)
	{
		ADaisyReefGameMode::SpawnGameMapCommon({0, 0, 0}, {0, 0, 0}, GameMapClass);
	}
}

ADaisyReefGameMap* ADaisyReefGameMode::SpawnGameMapCommon(const FVector& SpawnLocation, const FRotator& SpawnRotation,
                                                          const TSubclassOf<ADaisyReefGameMap> GameMap)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient; // We never want to save player controllers into a map
	SpawnInfo.bDeferConstruction = true;
	ADaisyReefGameMap* NewGameMap = GetWorld()->SpawnActor<ADaisyReefGameMap>(
		GameMap, SpawnLocation, SpawnRotation, SpawnInfo);

	if (NewGameMap)
	{
		UGameplayStatics::FinishSpawningActor(NewGameMap, FTransform(SpawnRotation, SpawnLocation));
	}

	return NewGameMap;
}
