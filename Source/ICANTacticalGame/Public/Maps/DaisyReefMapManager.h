// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/DaisyReefMapElement.h"
#include "GameFramework/Actor.h"
#include "Objects/Maps/DaisyReefMapObject.h"
#include "DaisyReefMapManager.generated.h"

class ADaisyReefMapGenerator;

USTRUCT(BlueprintType)
struct FElementByLocation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ShowTreeView))
	ADaisyReefMapElement* MapElement = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Location = FVector::ZeroVector;
};

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

	/**
	 * @brief TEST
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="DaisyReef|Map")
	TArray<FElementByLocation> TestSurround = {};

	/**
	 * @brief 
	 * @param StartElement 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	TArray<FElementByLocation> SurroundElement(FElementByLocation StartElement, TArray<ADaisyReefMapElement*> ElementsToCheck);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	ADaisyReefMapGenerator* MapGenerator = nullptr;
};
