﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/DaisyReefMapElement.h"
#include "GameFramework/Actor.h"
#include "Objects/Maps/DaisyReefMapObject.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|TextureMap", meta=(ShowTreeView))
	TSubclassOf<UDaisyReefMapObject> MapProperty;

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

	/**
	 * @brief TEST
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="DaisyReef|Map")
	TArray<ADaisyReefMapElement*> TestSurround = {};

	/**
	 * @brief 
	 * @param StartLocation
	 * @param Radius
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	TArray<ADaisyReefMapElement*> SurroundElement(const FVector StartLocation, const FVector Radius) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	ADaisyReefMapGenerator* MapGenerator = nullptr;
};
