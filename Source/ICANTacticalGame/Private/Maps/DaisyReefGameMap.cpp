// Fill out your copyright notice in the Description page of Project Settings.

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
	if (MapProperty.GetDefaultObject()->MapProperties.TextureMap != nullptr)
	{
		FElementListByTagAndLocation ElementListByTagAndLocation = GetElementListByTagAndLocation(
			MapProperty.GetDefaultObject()->MapElementsByTile, "Floor", false);
		if (ElementListByTagAndLocation.MapElement != nullptr)
		{
			FloorMapElementsSpawned = GenerateGridMapElementByTexture(
				GenerateColorMapList(MapProperty.GetDefaultObject()->MapProperties, ElementListByTagAndLocation),
				MapProperty.GetDefaultObject()->MapProperties, ElementListByTagAndLocation
				,
				0, "Floor");
		}

		ElementListByTagAndLocation = GetElementListByTagAndLocation(MapProperty.GetDefaultObject()->MapElementsByTile,
		                                                             "Wall", true);
		if (ElementListByTagAndLocation.MapElement != nullptr)
		{
			WallMapElementsSpawned = GenerateTileMapElementByTexture(
				GenerateColorMapList(MapProperty.GetDefaultObject()->MapProperties,
				                     ElementListByTagAndLocation), MapProperty.GetDefaultObject()->MapProperties,
				ElementListByTagAndLocation,
				100, "Wall");
		}
	}
}

TArray<FColorListByLocation> ADaisyReefGameMap::GenerateColorMapList(const FMapProperties MapProperties,
                                                                     const FElementListByTagAndLocation
                                                                     ElementListByTagAndLocation)
{
	UE_LOG(LogGameMap, Display, TEXT("Generate new ColorList with %s"), *MapProperties.TextureMap->GetName());

	TArray<FColorListByLocation> NewColorList = {};

	const TextureCompressionSettings OldCompressionSettings = MapProperties.TextureMap->CompressionSettings;
	const TextureMipGenSettings OldMipGenSettings = MapProperties.TextureMap->MipGenSettings;
	const bool OldSRGB = MapProperties.TextureMap->SRGB;

	MapProperties.TextureMap->CompressionSettings = TC_VectorDisplacementmap;
	MapProperties.TextureMap->MipGenSettings = TMGS_NoMipmaps;
	MapProperties.TextureMap->SRGB = false;
	MapProperties.TextureMap->UpdateResource();

	const auto PlatformDataTexture = MapProperties.TextureMap->GetPlatformData();

	const FColor* FormattedImageData = static_cast<const FColor*>(PlatformDataTexture->Mips[0].BulkData.LockReadOnly());

	for (int32 y = 0; y < MapProperties.TextureMap->GetSizeY(); y++)
	{
		for (int32 x = 0; x < MapProperties.TextureMap->GetSizeX(); x++)
		{
			if (const FColor PixelColor = FormattedImageData[y * MapProperties.TextureMap->GetSizeX() + x]; PixelColor.A
				== 255)
			{
				FColorListByLocation NewColorByLocation;
				NewColorByLocation.Color = PixelColor;
				NewColorByLocation.Location = {x, y};
				NewColorList.Add(NewColorByLocation);
			}
		}
	}

	PlatformDataTexture->Mips[0].BulkData.Unlock();

	MapProperties.TextureMap->CompressionSettings = OldCompressionSettings;
	MapProperties.TextureMap->MipGenSettings = OldMipGenSettings;
	MapProperties.TextureMap->SRGB = OldSRGB;
	MapProperties.TextureMap->UpdateResource();

	return NewColorList;
}

TArray<ADaisyReefMapElement*> ADaisyReefGameMap::GenerateGridMapElementByTexture(
	TArray<FColorListByLocation> ColorList, const FMapProperties MapProperties,
	FElementListByTagAndLocation ElementListByTagAndLocation, const float HeightLocation, const FName TargetTag)
{
	TArray<ADaisyReefMapElement*> NewMapElementsTexture = {};

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient; // We never want to save player controllers into a map
	SpawnInfo.bDeferConstruction = true;

	auto [Tag, ColorNeededToSpawnCube, MapElement, TextureLocation, TextureSize] = ElementListByTagAndLocation;

	for (auto [Color, Location] : ColorList)
	{
		if (Color == ColorNeededToSpawnCube && ((Location.WidthX >= TextureLocation.WidthX && Location.WidthX <
			TextureLocation.WidthX + TextureSize.WidthX) && (Location.WidthY >= TextureLocation.WidthY && Location.
			WidthY < TextureLocation.WidthY + TextureSize.WidthY)) && Tag == TargetTag)
		{
			FVector NewElementLocation = GetNewPosition(MapProperties.MapLocation, FVector(Location.WidthX, Location.WidthY, HeightLocation), {TextureLocation.WidthX, TextureLocation.WidthY}, {TextureSize.WidthX, TextureSize.WidthY}, {MapProperties.GridOffset.WidthX, MapProperties.GridOffset.WidthY});
			if (ADaisyReefMapElement* NewMapElement = GetWorld()->SpawnActor<ADaisyReefMapElement>(
				MapElement, NewElementLocation, FRotator::ZeroRotator, SpawnInfo))
			{
				UGameplayStatics::FinishSpawningActor(NewMapElement,
				                                      FTransform(FRotator::ZeroRotator, NewElementLocation));
				NewMapElementsTexture.Add(NewMapElement);
			}
		}
	}

	return NewMapElementsTexture;
}

TArray<ADaisyReefMapElement*> ADaisyReefGameMap::GenerateTileMapElementByTexture(
	TArray<FColorListByLocation> ColorList, const FMapProperties MapProperties,
	FElementListByTagAndLocation ElementListByTagAndLocation, const float HeightLocation, const FName TargetTag)
{
	TArray<ADaisyReefMapElement*> NewMapElementsTexture = {};

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient; // We never want to save player controllers into a map
	SpawnInfo.bDeferConstruction = true;

	auto [Tag, ColorNeededToSpawnCube, MapElement, TextureLocation, TextureSize] = ElementListByTagAndLocation;

	for (auto [Color, Location] : ColorList)
	{
		if (Color == ColorNeededToSpawnCube && ((Location.WidthX >=
			TextureLocation.WidthX && Location.WidthX <
			TextureLocation.WidthX + TextureSize.WidthX) && (Location.WidthY >=
			TextureLocation.WidthY && Location.WidthY <
			TextureLocation.WidthY + TextureSize.WidthY)))
		{
			FVector NewElementLocation = GetNewPosition(MapProperties.MapLocation, FVector(Location.WidthX, Location.WidthY, HeightLocation), {TextureLocation.WidthX, TextureLocation.WidthY}, {TextureSize.WidthX, TextureSize.WidthY}, {MapProperties.GridOffset.WidthX, MapProperties.GridOffset.WidthY});
			if (ADaisyReefMapElement* NewMapElement = GetWorld()->SpawnActor<ADaisyReefMapElement>(
				ElementListByTagAndLocation.MapElement, NewElementLocation, FRotator::ZeroRotator, SpawnInfo))
			{
				UGameplayStatics::FinishSpawningActor(NewMapElement,
				                                      FTransform(
					                                      FRotator::ZeroRotator, NewElementLocation));
				NewMapElementsTexture.Add(NewMapElement);
			}
		}
	}

	return NewMapElementsTexture;
}

FElementListByTagAndLocation ADaisyReefGameMap::GetElementListByTagAndLocation(
	TArray<FElementListByTagAndLocation> ElementListByTagAndLocations, const FName TargetTag, const bool bUseRandom)
{
	TArray<FElementListByTagAndLocation> SelectedElements = {};
	FElementListByTagAndLocation NewElement;

	for (auto SelectedElement : ElementListByTagAndLocations)
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

FVector ADaisyReefGameMap::GetNewPosition(const FVector TargetLocation, const FVector CurrentLocation, const FVector2DInt PixelLocation, const FVector2DInt Size, const FVector2DInt GridOffset)
{
	const FVector2d HalfSize = FVector2d(Size.WidthX / 2.0f, Size.WidthY / 2.0f);
	const float X = FMath::GetMappedRangeValueClamped(FVector2d(PixelLocation.WidthX, PixelLocation.WidthX + Size.WidthX), FVector2d(TargetLocation.X - HalfSize.X, TargetLocation.X + HalfSize.X), CurrentLocation.X) * GridOffset.WidthX;
	const float Y = FMath::GetMappedRangeValueClamped(FVector2d(PixelLocation.WidthY, PixelLocation.WidthY + Size.WidthY), FVector2d(TargetLocation.Y - HalfSize.Y, TargetLocation.Y + HalfSize.Y), CurrentLocation.Y) * GridOffset.WidthY;
	const float Z = CurrentLocation.Z;
	
	return FVector(X, Y, Z);
}
