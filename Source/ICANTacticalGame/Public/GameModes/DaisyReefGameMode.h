// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DaisyReefTeam.h"
#include "GameFramework/GameModeBase.h"
#include "DaisyReefGameMode.generated.h"

class ADaisyReefMapManager;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ICANTACTICALGAME_API ADaisyReefGameMode : public AGameModeBase
{
	GENERATED_UCLASS_BODY()
public:
	/** Class of GameMap, used to generate map on Start */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Classes, meta=(ShowTreeView))
	TSubclassOf<ADaisyReefMapManager> GameMapClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Classes, meta=(ShowTreeView))
	TSubclassOf<ADaisyReefTeam> GameTeamsClass = nullptr;

	UFUNCTION(BlueprintCallable, Category="DaisyReef|GameMapClass")
	ADaisyReefMapManager* GetGameMap() const;

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual ADaisyReefMapManager* SpawnGameMapCommon(const FVector& SpawnLocation, const FRotator& SpawnRotation,
	                                              TSubclassOf<ADaisyReefMapManager> GameMap);

	virtual ADaisyReefTeam* SpawnGameTeamsCommon(const FVector& SpawnLocation, const FRotator& SpawnRotation,
												  TSubclassOf<ADaisyReefTeam> GameTeam);

	UFUNCTION(BlueprintCallable)
	virtual ADaisyReefMapManager* GetMapManager();

	UFUNCTION(BlueprintCallable)
	virtual ADaisyReefTeam* GetGameTeams();

private:
	ADaisyReefMapManager* SpawnedGameMap = nullptr;
	ADaisyReefTeam* SpawnedGameTeams = nullptr;
};
