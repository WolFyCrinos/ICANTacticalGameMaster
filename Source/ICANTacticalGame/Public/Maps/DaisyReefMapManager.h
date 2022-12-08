﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/DaisyReefMapElement.h"
#include "GameFramework/Actor.h"
#include "DaisyReefMapManager.generated.h"

class ADaisyReefMapGenerator;

UCLASS(Blueprintable, BlueprintType)
class ICANTACTICALGAME_API ADaisyReefMapManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADaisyReefMapManager();

	/**
	* @brief 
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="DaisyReef|Properties")
	TSubclassOf<ADaisyReefMapGenerator> MapGeneratorClass = nullptr;
	
	/**
	 * @brief 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="DaisyReef|Map")
	TArray<ADaisyReefMapElement*> WallMapElementsSpawned;

	/**
	 * @brief 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="DaisyReef|Map")
	TArray<ADaisyReefMapElement*> FloorMapElementsSpawned;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	ADaisyReefMapGenerator* MapGenerator = nullptr;
};