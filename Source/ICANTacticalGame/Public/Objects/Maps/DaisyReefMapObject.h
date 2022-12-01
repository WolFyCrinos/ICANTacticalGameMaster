﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DaisyReefMapObject.generated.h"

class ADaisyReefMapElement;

UENUM()
enum class ETileOrientation : uint8
{
	Default,
	MirrorX,
	MirrorY,
	MirrorXY
};

USTRUCT(BlueprintType)
struct FVector2DInt
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ForceUnits="units", ClampMin=0))
	int WidthX = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ForceUnits="units", ClampMin=0))
	int WidthY = 0;
};

USTRUCT(BlueprintType)
struct FMapProperties
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|MapElementsProperties")
	UTexture2D* TextureMap = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2DInt GridOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector MapLocation;
};

USTRUCT(BlueprintType)
struct FElementListByTagAndLocation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|TextureMap")
	FName Tag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FColor ColorNeededToSpawnCube;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ShowTreeView))
	TSubclassOf<ADaisyReefMapElement> MapElement = nullptr;

	/**
	 * @brief Warning ! Textures are Read TopLeft -> BottomRight
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|TextureMap")
	FVector2DInt TextureLocation = {0, 0};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|TextureMap")
	FVector2DInt TextureSize = {0, 0};
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ICANTACTICALGAME_API UDaisyReefMapObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|MapProperties")
	FMapProperties MapProperties;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|MapElementsProperties", meta=(DeprecatedProperty))
	TArray<FElementListByTagAndLocation> MapElementsByTile;
};
