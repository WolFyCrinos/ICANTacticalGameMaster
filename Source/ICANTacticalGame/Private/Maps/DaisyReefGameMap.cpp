// Fill out your copyright notice in the Description page of Project Settings.

#include "Maps/DaisyReefGameMap.h"

#include "Actors/DaisyReefMapElement.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/Maps/DaisyReefMapObject.h"
#include "Rendering/Texture2DResource.h"

// Sets default values
ADaisyReefGameMap::ADaisyReefGameMap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ADaisyReefGameMap::BeginPlay()
{
	ColorList.Empty();

	if (MapProperty.GetDefaultObject()->MapProperties.TextureMap != nullptr)
	{
		ColorList = GenerateColorMapList(MapProperty.GetDefaultObject()->MapProperties.TextureMap, ETileOrientation::HG);
		if (!ColorList.IsEmpty() && MapProperty.GetDefaultObject()->SingleMapElements != nullptr)
		{
			FloorMapElementsSpawned = GenerateGridBySingleMapElement(MapProperty.GetDefaultObject()->MapProperties.TextureMap, MapProperty.GetDefaultObject()->SingleMapElements, 0);
		}	
		if (!ColorList.IsEmpty() && !MapProperty.GetDefaultObject()->MapElementsByTile.IsEmpty())
		{
			MapElementsSpawned = GenerateTileMapElementByTexture(MapProperty.GetDefaultObject()->MapProperties.TextureMap, ColorList, MapProperty.GetDefaultObject()->MapElementsByTile, 100);
		}
	}
}

TArray<FColor> ADaisyReefGameMap::GenerateColorMapList(const UTexture2D* TextureMap, ETileOrientation TileOrientation)
{
	TArray<FColor>  NewColorList = {};
	
	const TextureCompressionSettings OldCompressionSettings = MapProperty.GetDefaultObject()->MapProperties.TextureMap->CompressionSettings;
	const TextureMipGenSettings OldMipGenSettings = MapProperty.GetDefaultObject()->MapProperties.TextureMap->MipGenSettings;
	const bool OldSRGB = MapProperty.GetDefaultObject()->MapProperties.TextureMap->SRGB;

	MapProperty.GetDefaultObject()->MapProperties.TextureMap->CompressionSettings = TextureCompressionSettings::TC_Default;
	MapProperty.GetDefaultObject()->MapProperties.TextureMap->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
	MapProperty.GetDefaultObject()->MapProperties.TextureMap->SRGB = true;
	MapProperty.GetDefaultObject()->MapProperties.TextureMap->UpdateResource();

	const auto PlatformDataTexture = MapProperty.GetDefaultObject()->MapProperties.TextureMap->GetPlatformData();

	const FColor* FormattedImageData = static_cast<const FColor*>(PlatformDataTexture->Mips[0].BulkData.LockReadOnly());
		
	for (int32 y = 0; y < MapProperty.GetDefaultObject()->MapProperties.TextureMap->GetSizeY(); ++y)
	{
		for (int32 x = 0; x < MapProperty.GetDefaultObject()->MapProperties.TextureMap->GetSizeX(); ++x)
		{
			if (FColor PixelColor = FormattedImageData[y * MapProperty.GetDefaultObject()->MapProperties.TextureMap->GetSizeX() + x]; PixelColor.A == 255)
			{
				NewColorList.Add(PixelColor);
			}
		}
	}

	PlatformDataTexture->Mips[0].BulkData.Unlock();

	MapProperty.GetDefaultObject()->MapProperties.TextureMap->CompressionSettings = OldCompressionSettings;
	MapProperty.GetDefaultObject()->MapProperties.TextureMap->MipGenSettings = OldMipGenSettings;
	MapProperty.GetDefaultObject()->MapProperties.TextureMap->SRGB = OldSRGB;
	MapProperty.GetDefaultObject()->MapProperties.TextureMap->UpdateResource();

	return NewColorList;
}

TArray<ADaisyReefMapElement*> ADaisyReefGameMap::GenerateGridBySingleMapElement(const UTexture2D* TextureMap,
                                                                                const TSubclassOf<ADaisyReefMapElement> MapElement, const float HeightLocation)
{
	TArray<ADaisyReefMapElement*> NewFloorElementMap = {};
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient; // We never want to save player controllers into a map
	SpawnInfo.bDeferConstruction = true;
	
	for (int32 y = 0; y < MapProperty.GetDefaultObject()->MapProperties.TextureMap->GetSizeY(); ++y)
	{
		for (int32 x = 0; x < MapProperty.GetDefaultObject()->MapProperties.TextureMap->GetSizeX(); ++x)
		{
			FVector NewElementLocation = FVector(
				x * MapProperty.GetDefaultObject()->MapProperties.GridOffset.WidthX,
				y * MapProperty.GetDefaultObject()->MapProperties.GridOffset.WidthY,
				HeightLocation);

			if (ADaisyReefMapElement* NewMapElement = GetWorld()->SpawnActor<ADaisyReefMapElement>(
				MapElement, NewElementLocation, FRotator::ZeroRotator, SpawnInfo))
			{
				UGameplayStatics::FinishSpawningActor(NewMapElement,
													  FTransform(
														  FRotator::ZeroRotator, NewElementLocation));
				NewFloorElementMap.Add(NewMapElement);
			}
		}
	}

	return NewFloorElementMap;
}

TArray<ADaisyReefMapElement*> ADaisyReefGameMap::GenerateGridMapElementByTexture(const UTexture2D* TextureMap,
	const TArray<FColor> Colors, const TArray<FMapElement> MapPropertyClass, const float HeightLocation)
{
	TArray<ADaisyReefMapElement*> NewFloorElementMap = {};
	int Index = 0;
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient; // We never want to save player controllers into a map
	SpawnInfo.bDeferConstruction = true;
	
	for (int32 y = 0; y < MapProperty.GetDefaultObject()->MapProperties.TextureMap->GetSizeY(); ++y)
	{
		for (int32 x = 0; x < MapProperty.GetDefaultObject()->MapProperties.TextureMap->GetSizeX(); ++x)
		{
			FVector NewElementLocation = FVector(
				x * MapProperty.GetDefaultObject()->MapProperties.GridOffset.WidthX,
				y * MapProperty.GetDefaultObject()->MapProperties.GridOffset.WidthY,
				HeightLocation);

			for (auto [ColorNeededToSpawnCube, MapElement] : MapPropertyClass)
			{
				if (Colors[Index] == ColorNeededToSpawnCube)
				{
					if (ADaisyReefMapElement* NewMapElement = GetWorld()->SpawnActor<ADaisyReefMapElement>(
						MapElement, NewElementLocation, FRotator::ZeroRotator, SpawnInfo))
					{
						UGameplayStatics::FinishSpawningActor(NewMapElement,
															  FTransform(
																  FRotator::ZeroRotator, NewElementLocation));
						NewFloorElementMap.Add(NewMapElement);
					}
				}
			}
			
			Index = FMath::Clamp(++Index, 0, (MapProperty.GetDefaultObject()->MapProperties.TextureMap->GetSizeY() * MapProperty.GetDefaultObject()->MapProperties.TextureMap->GetSizeX() - 1));
		}
	}

	return NewFloorElementMap;
}

TArray<ADaisyReefMapElement*> ADaisyReefGameMap::GenerateTileMapElementByTexture(const UTexture2D* TextureMap,
	const TArray<FColor> Colors, const TArray<FMapTileElement> MapPropertyClass, const float HeightLocation)
{
	TArray<ADaisyReefMapElement*> NewFloorElementMap = {};
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient; // We never want to save player controllers into a map
	SpawnInfo.bDeferConstruction = true;
	
	for (auto [ColorNeededToSpawnCube, TextureMapMask, TileOrientation, MapElement] : MapPropertyClass)
	{
		int IndexMap = 0;
		int IndexMask = 0;
		TArray<FColor> ColorsMask = GenerateColorMapList(TextureMapMask, TileOrientation);
		
		for (int32 y = 0; y < MapProperty.GetDefaultObject()->MapProperties.TextureMap->GetSizeY(); ++y)
		{
			for (int32 x = 0; x < MapProperty.GetDefaultObject()->MapProperties.TextureMap->GetSizeX(); ++x)
			{
				if (Colors[IndexMap] == ColorNeededToSpawnCube)
				{
					FVector NewElementLocation = FVector(
							x * MapProperty.GetDefaultObject()->MapProperties.GridOffset.WidthX,
							y * MapProperty.GetDefaultObject()->MapProperties.GridOffset.WidthY,
							HeightLocation);

					if (ColorsMask[IndexMask] != FColor::Black)
					{
						if (ADaisyReefMapElement* NewMapElement = GetWorld()->SpawnActor<ADaisyReefMapElement>(
						MapElement, NewElementLocation, FRotator::ZeroRotator, SpawnInfo))
						{
							UGameplayStatics::FinishSpawningActor(NewMapElement,
																  FTransform(
																	  FRotator::ZeroRotator, NewElementLocation));
							NewFloorElementMap.Add(NewMapElement);
						}
					}

					IndexMask = FMath::Clamp(++IndexMask, 0, (TextureMapMask->GetSizeY() * TextureMapMask->GetSizeX() - 1));
				}
						
				IndexMap = FMath::Clamp(++IndexMap, 0, (MapProperty.GetDefaultObject()->MapProperties.TextureMap->GetSizeY() * MapProperty.GetDefaultObject()->MapProperties.TextureMap->GetSizeX() - 1));
			}
		}
	}
	
	return NewFloorElementMap;
}
