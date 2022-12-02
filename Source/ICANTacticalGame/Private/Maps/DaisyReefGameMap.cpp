﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Maps/DaisyReefGameMap.h"
#include "Actors/DaisyReefMapElement.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/Maps/DaisyReefMapObject.h"
#include "Rendering/Texture2DResource.h"

DEFINE_LOG_CATEGORY(LogGameMap);

// Sets default values
ADaisyReefGameMap::ADaisyReefGameMap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ADaisyReefGameMap::BeginPlay()
{
	for (const auto [TextureTag, TextureMap] : MapProperty.GetDefaultObject()->MapProperties.TextureMap)
	{
		if (TextureMap != nullptr)
		{
			for (const auto [Tag, Location] : MapProperty.GetDefaultObject()->MapProperties.TagsToSpawn)
			{
				if (TextureTag == Tag)
				{
					FElementList ElementListByTagAndLocation = GetElementListByTagAndLocation(
						MapProperty.GetDefaultObject()->MapElementsByTile, Tag, Tag == "Floor" ? false : true);
					if (ElementListByTagAndLocation.MapElement != nullptr)
					{
						FloorMapElementsSpawned = GenerateTileMapElementByTexture(
							GenerateColorMapList(TextureMap), MapProperty.GetDefaultObject()->MapProperties,
							ElementListByTagAndLocation, Tag, Location);
					}
				}
			}
		}
	}
}

TArray<FColorListByLocation> ADaisyReefGameMap::GenerateColorMapList(UTexture2D* Texture)
{
	UE_LOG(LogGameMap, Display, TEXT("Generate new ColorList with %s"), *Texture->GetName());

	TArray<FColorListByLocation> NewColorList = {};

	const TextureCompressionSettings OldCompressionSettings = Texture->CompressionSettings;
	const TextureMipGenSettings OldMipGenSettings = Texture->MipGenSettings;
	const bool OldSRGB = Texture->SRGB;

	Texture->CompressionSettings = TC_VectorDisplacementmap;
	Texture->MipGenSettings = TMGS_NoMipmaps;
	Texture->SRGB = 0;
	Texture->UpdateResource();

	const auto PlatformDataTexture = Texture->GetPlatformData();

	FColor* FormattedImageData = nullptr;
	PlatformDataTexture->Mips[0].BulkData.GetCopy(reinterpret_cast<void**>(&FormattedImageData));

	const int32 TextSizeY = Texture->GetSizeY();
	const int32 TextSizeX = Texture->GetSizeX();

	for (int32 y = 0; y < TextSizeY; y++)
	{
		for (int32 x = 0; x < TextSizeX; x++)
		{
			if (const FColor PixelColor = FormattedImageData[y * Texture->GetSizeX() + x]; PixelColor.A
				== 255)
			{
				FColorListByLocation NewColorByLocation;
				NewColorByLocation.Color = PixelColor;
				NewColorByLocation.Location = {x, y};
				NewColorList.Add(NewColorByLocation);
			}
		}
	}

	Texture->CompressionSettings = OldCompressionSettings;
	Texture->MipGenSettings = OldMipGenSettings;
	Texture->SRGB = OldSRGB;
	Texture->UpdateResource();

	return NewColorList;
}

TArray<ADaisyReefMapElement*> ADaisyReefGameMap::GenerateTileMapElementByTexture(
	TArray<FColorListByLocation> ColorList, const FMapProperties MapProperties,
	FElementList ElementList, const FName TargetTag, const FVector Location)
{
	TArray<ADaisyReefMapElement*> NewMapElementsTexture = {};

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient; // We never want to save player controllers into a map
	SpawnInfo.bDeferConstruction = true;

	auto [Tag, ColorNeededToSpawnCube, MapElement, TextureLocation, TextureSize] = ElementList;

	for (auto [Color, ColorLocation] : ColorList)
	{
		if (Color == ColorNeededToSpawnCube && ((ColorLocation.WidthX >=
			TextureLocation.WidthX && ColorLocation.WidthX <
			TextureLocation.WidthX + TextureSize.WidthX) && (ColorLocation.WidthY >=
			TextureLocation.WidthY && ColorLocation.WidthY <
			TextureLocation.WidthY + TextureSize.WidthY)))
		{
			FVector NewElementLocation = GetNewPosition(
				Location, FVector(ColorLocation.WidthX, ColorLocation.WidthY, Location.Z),
				{TextureLocation.WidthX, TextureLocation.WidthY}, {TextureSize.WidthX, TextureSize.WidthY}, {
					MapProperties.GridOffset.WidthX, MapProperties.GridOffset.WidthY
				});
			if (ADaisyReefMapElement* NewMapElement = GetWorld()->SpawnActor<ADaisyReefMapElement>(
				ElementList.MapElement, NewElementLocation, FRotator::ZeroRotator, SpawnInfo))
			{
				UGameplayStatics::FinishSpawningActor(NewMapElement,
				                                      FTransform(
					                                      FRotator::ZeroRotator, NewElementLocation));
				NewMapElementsTexture.Add(NewMapElement);
			}
		}
		/** DEBUG */
		else if (Color != ColorNeededToSpawnCube)
		{
			UE_LOG(LogGameMap, Warning, TEXT("Error Color with %s != %s"), *Color.ToString(),
			       *ColorNeededToSpawnCube.ToString());
		}
		else if (Color.A != 255)
		{
			UE_LOG(LogGameMap, Warning, TEXT("Error Alpha Color with %s"), *Color.ToString());
		}
	}

	return NewMapElementsTexture;
}

FElementList ADaisyReefGameMap::GetElementListByTagAndLocation(
	TArray<FElementList> ElementList, const FName TargetTag, const bool bUseRandom)
{
	TArray<FElementList> SelectedElements = {};
	FElementList NewElement;

	for (auto SelectedElement : ElementList)
	{
		if (SelectedElement.Tag == TargetTag)
		{
			SelectedElements.Add(SelectedElement);
		}
	}

	return bUseRandom
		       ? SelectedElements[FMath::RandRange(0, SelectedElements.IsEmpty()
			                                              ? 0
			                                              : SelectedElements.Num() - 1)]
		       : SelectedElements[0];
}

FVector ADaisyReefGameMap::GetNewPosition(const FVector TargetLocation, const FVector CurrentLocation,
                                          const FVector2DInt PixelLocation, const FVector2DInt Size,
                                          const FVector2DInt GridOffset)
{
	const FVector2d HalfSize = FVector2d(Size.WidthX / 2.0f, Size.WidthY / 2.0f);
	const float X = FMath::GetMappedRangeValueClamped(
		FVector2d(PixelLocation.WidthX, PixelLocation.WidthX + Size.WidthX),
		FVector2d(TargetLocation.X - HalfSize.X, TargetLocation.X + HalfSize.X), CurrentLocation.X) * GridOffset.WidthX;
	const float Y = FMath::GetMappedRangeValueClamped(
		FVector2d(PixelLocation.WidthY, PixelLocation.WidthY + Size.WidthY),
		FVector2d(TargetLocation.Y - HalfSize.Y, TargetLocation.Y + HalfSize.Y), CurrentLocation.Y) * GridOffset.WidthY;
	const float Z = CurrentLocation.Z;

	return FVector(X, Y, Z);
}
