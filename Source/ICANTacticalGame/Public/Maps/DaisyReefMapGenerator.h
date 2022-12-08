// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/Maps/DaisyReefMapObject.h"
#include "Actors/DaisyReefMapElement.h"
#include "DaisyReefMapGenerator.generated.h"

class UDaisyReefMapObject;

ICANTACTICALGAME_API DECLARE_LOG_CATEGORY_EXTERN(LogGameMap, Display, All);

USTRUCT(BlueprintType)
struct FColorListByLocation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|TextureMap")
	FColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|TextureMap")
	FVector2DInt Location;
};


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ICANTACTICALGAME_API ADaisyReefMapGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ADaisyReefMapGenerator();

	/**
	 * @brief
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|TextureMap", meta=(ShowTreeView))
	TSubclassOf<UDaisyReefMapObject> MapProperty;

	/**
	 * @brief 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual TArray<ADaisyReefMapElement*> BeginGenerate();

protected:
	/**
	 * @brief This Function Generate a TArray of FColor with all colors on Texture2D
	 * @param Texture Give the Texture2D to get all pixel FColors and Locations
	 * @return Return a TArray of FColorByLocation with the pixel FColor and the pixel Location on the Texture
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual TArray<FColorListByLocation> GenerateColorMapList(UTexture2D* Texture);

	/**
	 * @brief 
	 * @param ColorList 
	 * @param MapProperties 
	 * @param ElementList 
	 * @param TargetTag
	 * @param bIsWalkable 
	 * @param Location 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual TArray<ADaisyReefMapElement*> GenerateTileMapElementByTexture(
		TArray<FColorListByLocation> ColorList, const FMapProperties MapProperties,
		FElementList ElementList, const FName TargetTag, const FVector Location);

	/**
	 * @brief 
	 * @param ElementList 
	 * @param TargetTag 
	 * @param bUseRandom 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual FElementList GetElementListByTagAndLocation(
		TArray<FElementList> ElementList, const FName TargetTag,
		const bool bUseRandom = false);

	/**
	 * @brief 
	 * @param TargetLocation 
	 * @param CurrentLocation 
	 * @param PixelLocation 
	 * @param Size 
	 * @param GridOffset 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual FVector GetNewPosition(const FVector TargetLocation, const FVector CurrentLocation,
								   const FVector2DInt PixelLocation, const FVector2DInt Size,
								   const FVector2DInt GridOffset);
};
