// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/DaisyReefGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Maps/DaisyReefMapManager.h"

ADaisyReefGameMode::ADaisyReefGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.DoNotCreateDefaultSubobject(TEXT("Sprite")))
{
	GameMapClass = nullptr;
}


ADaisyReefMapManager* ADaisyReefGameMode::GetGameMap() const
{
	return SpawnedGameMap;
}

void ADaisyReefGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	if (GameMapClass)
	{
		SpawnedGameMap = ADaisyReefGameMode::SpawnGameMapCommon(FVector::ZeroVector, FRotator::ZeroRotator, GameMapClass);
	}

	if (GameTeamsClass)
	{
		SpawnedGameTeams = ADaisyReefGameMode::SpawnGameTeamsCommon(FVector::ZeroVector, FRotator::ZeroRotator, GameTeamsClass);
	}
}

ADaisyReefMapManager* ADaisyReefGameMode::SpawnGameMapCommon(const FVector& SpawnLocation, const FRotator& SpawnRotation,
                                                          const TSubclassOf<ADaisyReefMapManager> GameMap)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient; // We never want to save player controllers into a map
	SpawnInfo.bDeferConstruction = true;
	ADaisyReefMapManager* NewGameMap = GetWorld()->SpawnActor<ADaisyReefMapManager>(
		GameMap, SpawnLocation, SpawnRotation, SpawnInfo);

	if (NewGameMap)
	{
		UGameplayStatics::FinishSpawningActor(NewGameMap, FTransform(SpawnRotation, SpawnLocation));
	}

	return NewGameMap;
}


ADaisyReefTeam* ADaisyReefGameMode::SpawnGameTeamsCommon(const FVector& SpawnLocation, const FRotator& SpawnRotation,
														  const TSubclassOf<ADaisyReefTeam> GameTeam)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient; // We never want to save player controllers into a map
	SpawnInfo.bDeferConstruction = true;
	ADaisyReefTeam* NewGameMap = GetWorld()->SpawnActor<ADaisyReefTeam>(
		GameTeam, SpawnLocation, SpawnRotation, SpawnInfo);

	if (NewGameMap)
	{
		UGameplayStatics::FinishSpawningActor(NewGameMap, FTransform(SpawnRotation, SpawnLocation));
	}

	return NewGameMap;
}

ADaisyReefMapManager* ADaisyReefGameMode::GetMapManager()
{
	return SpawnedGameMap;
}

ADaisyReefTeam* ADaisyReefGameMode::GetGameTeams()
{
	return SpawnedGameTeams;
}
