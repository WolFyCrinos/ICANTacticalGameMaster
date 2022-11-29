// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DaisyReefGameMode.generated.h"

class ADaisyReefGameMap;

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
	TSubclassOf<ADaisyReefGameMap> GameMapClass = nullptr;

	UFUNCTION(BlueprintCallable, Category="DaisyReef|GameMapClass")
	ADaisyReefGameMap* GetGameMap() const;

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual ADaisyReefGameMap* SpawnGameMapCommon(const FVector& SpawnLocation, const FRotator& SpawnRotation,
	                                              TSubclassOf<ADaisyReefGameMap> GameMap);

private:
	ADaisyReefGameMap* SpawnedGameMap = nullptr;
};
