// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/DaisyReefMapElement.h"

#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ADaisyReefMapElement::ADaisyReefMapElement()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADaisyReefMapElement::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADaisyReefMapElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ADaisyReefMapElement::GetIsWalkable()
{
	return bIsWalkable;
}

void ADaisyReefMapElement::SetIsWalkable(bool SetIsWalkable)
{
	bIsWalkable = SetIsWalkable;
}

int ADaisyReefMapElement::GetF()
{
	return G + H;
}

int ADaisyReefMapElement::GetG()
{
	return G;
}

int ADaisyReefMapElement::GetH()
{
	return H;
}

void ADaisyReefMapElement::SetG(int NewG)
{
	G = NewG;
}

void ADaisyReefMapElement::SetH(int NewH)
{
	H = NewH;
}

ADaisyReefMapElement* ADaisyReefMapElement::GetPrevious()
{
	return  Previous;
}

void ADaisyReefMapElement::SetPrevious(ADaisyReefMapElement* NewPrevious)
{
	Previous = NewPrevious;
}

void ADaisyReefMapElement::FindNeighbour()
{
	TArray<ADaisyReefMapElement*> NewElement = {};
	TArray<FHitResult> Hits = {};

	UKismetSystemLibrary::BoxTraceMulti(GetWorld(), this->GetActorLocation(), this->GetActorLocation(), FVector(MapProperty.GetDefaultObject()->MapProperties.GridOffset.WidthX, MapProperty.GetDefaultObject()->MapProperties.GridOffset.WidthY, MapProperty.GetDefaultObject()->MapProperties.GridOffset.WidthX), FRotator::ZeroRotator, TraceTypeQuery1, false, {}, EDrawDebugTrace::Persistent, Hits, true);
	
	for (auto Hit : Hits)
	{
		ADaisyReefMapElement* SelectedElement = Cast<ADaisyReefMapElement>(Hit.GetActor());
		if (SelectedElement->IsValidLowLevel())
		{
			const bool SelfLocTest = !SelectedElement->GetActorLocation().Equals(this->GetActorLocation());
			const bool UpLeftLocTest = !SelectedElement->GetActorLocation().Equals(this->GetActorLocation() + FVector(-MapProperty.GetDefaultObject()->MapProperties.GridOffset.WidthX, MapProperty.GetDefaultObject()->MapProperties.GridOffset.WidthY, 0));
			const bool UpRightLocTest = !SelectedElement->GetActorLocation().Equals(this->GetActorLocation() + FVector(MapProperty.GetDefaultObject()->MapProperties.GridOffset.WidthX, MapProperty.GetDefaultObject()->MapProperties.GridOffset.WidthY, 0));
			const bool BottomLeftLocTest = !SelectedElement->GetActorLocation().Equals(this->GetActorLocation() + FVector(-MapProperty.GetDefaultObject()->MapProperties.GridOffset.WidthX, -MapProperty.GetDefaultObject()->MapProperties.GridOffset.WidthY, 0));
			const bool BottomRightLocTest = !SelectedElement->GetActorLocation().Equals(this->GetActorLocation() + FVector(MapProperty.GetDefaultObject()->MapProperties.GridOffset.WidthX, -MapProperty.GetDefaultObject()->MapProperties.GridOffset.WidthY, 0));
			
			if (SelectedElement->GetIsWalkable() && SelfLocTest && UpLeftLocTest && UpRightLocTest && BottomLeftLocTest && BottomRightLocTest)
			{
				NewElement.AddUnique(Cast<ADaisyReefMapElement>(Hit.GetActor()));
			}
		}
	}
	
	Neighbour = NewElement;
}

TArray<ADaisyReefMapElement*> ADaisyReefMapElement::GetNeighbour()
{
	return Neighbour;
}

void ADaisyReefMapElement::SetMapProperty(TSubclassOf<UDaisyReefMapObject> NewMapProperty)
{
	MapProperty = NewMapProperty;
}

void ADaisyReefMapElement::SetCurrentPawn(APawn* NewPawn)
{
	CurrentPlayer = NewPawn;
}

APawn* ADaisyReefMapElement::GetCurrentPawn()
{
	return CurrentPlayer;
}

bool ADaisyReefMapElement::HasAnyPawn()
{
	return CurrentPlayer != nullptr && CurrentPlayer->IsValidLowLevel();
}
