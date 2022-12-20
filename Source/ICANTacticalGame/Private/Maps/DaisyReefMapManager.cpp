// Fill out your copyright notice in the Description page of Project Settings.

#include "Maps/DaisyReefMapManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Maps/DaisyReefMapGenerator.h"

// Sets default values
ADaisyReefMapManager::ADaisyReefMapManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

TArray<ADaisyReefMapElement*> ADaisyReefMapManager::GetWalkableFloor()
{
	return FloorMapElementsSpawned;
}

TArray<ADaisyReefMapElement*> ADaisyReefMapManager::GetPawnSpawnerFloor()
{
	return PawnSpawnerMapElementsSpawned;
}

// Called when the game starts or when spawned
void ADaisyReefMapManager::BeginPlay()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient; // We never want to save player controllers into a map
	SpawnInfo.bDeferConstruction = true;

	if (MapGeneratorClass != nullptr)
	{
		MapGenerator = GetWorld()->SpawnActor<ADaisyReefMapGenerator>(MapGeneratorClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);

		UGameplayStatics::FinishSpawningActor(MapGenerator,FTransform(FRotator::ZeroRotator,  FVector::ZeroVector));
		
		for (auto Element : MapGenerator->BeginGenerate())
		{
			Element->SetMapProperty(MapProperty);
			if (Element->GetIsWalkable())
			{
				FloorMapElementsSpawned.AddUnique(Element);
			}
			else
			{
				FHitResult Hit;

				UKismetSystemLibrary::LineTraceSingle(GetWorld(), Element->GetActorLocation(), Element->GetActorLocation() + Element->GetActorUpVector() * -1000.0f, TraceTypeQuery1, false, {Cast<AActor>(Element)}, EDrawDebugTrace::Persistent, Hit, true);
				
				if(ADaisyReefMapElement* SelectedElement = Cast<ADaisyReefMapElement>(Hit.GetActor()); SelectedElement->IsValidLowLevel())
				{
					SelectedElement->SetIsWalkable(false);
				}
				
				WallMapElementsSpawned.AddUnique(Element);
			}

			if (Element->ActorHasTag(PawnSpawnerTag))
			{
				PawnSpawnerMapElementsSpawned.Add(Element);
			}
		}

		for (const auto Element : FloorMapElementsSpawned)
		{
			Element->FindNeighbour();
		}
	}
}

