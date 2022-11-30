// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/DaisyReefMapElement.h"
#include "GameFramework/Actor.h"
#include "Objects/Maps/DaisyReefMapObject.h"
#include "DaisyReefGameMap.generated.h"

class UDaisyReefMapObject;

UCLASS(Blueprintable, BlueprintType)
class ICANTACTICALGAME_API ADaisyReefGameMap : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADaisyReefGameMap();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|TactureMap", meta=(ShowTreeView))
	TSubclassOf<UDaisyReefMapObject> MapProperty;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|TactureMap")
	TArray<FColor> ColorList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|TactureMap")
	TArray<ADaisyReefMapElement*> MapElementsSpawned;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|TactureMap")
	TArray<ADaisyReefMapElement*> FloorMapElementsSpawned;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual TArray<FColor> GenerateColorMapList(const UTexture2D* TextureMap, ETileOrientation TileOrientation);

	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual TArray<ADaisyReefMapElement*> GenerateGridBySingleMapElement(const UTexture2D* TextureMap, const TSubclassOf<ADaisyReefMapElement> MapElement, const float HeightLocation);

	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual TArray<ADaisyReefMapElement*> GenerateGridMapElementByTexture(const UTexture2D* TextureMap, const TArray<FColor> Colors, const TArray<FMapElement> MapPropertyClass, const float HeightLocation);

	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual TArray<ADaisyReefMapElement*> GenerateTileMapElementByTexture(const UTexture2D* TextureMap, const TArray<FColor> Colors, const TArray<FMapTileElement> MapPropertyClass, const float HeightLocation);
};
