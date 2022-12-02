// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/DaisyReefMapElement.h"
#include "GameFramework/Actor.h"
#include "Objects/Maps/DaisyReefMapObject.h"
#include "DaisyReefGameMap.generated.h"

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

UCLASS(Blueprintable, BlueprintType)
class ICANTACTICALGAME_API ADaisyReefGameMap : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADaisyReefGameMap();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|TextureMap", meta=(ShowTreeView))
	TSubclassOf<UDaisyReefMapObject> MapProperty;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|TextureMap")
	TArray<ADaisyReefMapElement*> WallMapElementsSpawned;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|TextureMap")
	TArray<ADaisyReefMapElement*> FloorMapElementsSpawned;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual TArray<FColorListByLocation> GenerateColorMapList(UTexture2D* Texture,
	                                                          const FMapProperties MapProperties,
	                                                          const FElementList
	                                                          ElementList);

	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual TArray<ADaisyReefMapElement*> GenerateTileMapElementByTexture(
		TArray<FColorListByLocation> ColorList, const FMapProperties MapProperties,
		FElementList ElementList, const FName TargetTag, const FVector Location);

	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual FElementList GetElementListByTagAndLocation(
		TArray<FElementList> ElementList, const FName TargetTag,
		const bool bUseRandom = false);

	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual FVector GetNewPosition(const FVector TargetLocation, const FVector CurrentLocation,
	                               const FVector2DInt PixelLocation, const FVector2DInt Size,
	                               const FVector2DInt GridOffset);
};
