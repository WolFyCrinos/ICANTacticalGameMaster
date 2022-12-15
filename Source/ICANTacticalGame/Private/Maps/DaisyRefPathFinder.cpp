// Fill out your copyright notice in the Description page of Project Settings.

#include "Maps/DaisyRefPathFinder.h"
#include "Algo/RemoveIf.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY(LogPathFinder);

UDaisyRefPathFinder::UDaisyRefPathFinder()
{
	PrimaryComponentTick.bCanEverTick = true;
	SearchableElement.Empty();
}

TArray<ADaisyReefMapElement*> UDaisyRefPathFinder::FindPath(ADaisyReefMapElement* Start,
	ADaisyReefMapElement* End, TArray<ADaisyReefMapElement*> Range)
{
	UE_LOG(LogPathFinder, Display, TEXT("Start: %s, End: %s"), *Start->GetName(), *End->GetName());
	
	TArray<ADaisyReefMapElement*> OpenList = {};
	TArray<ADaisyReefMapElement*> ClosedList = {};

	OpenList.AddUnique(Start);

	while (!OpenList.IsEmpty())
	{
		Algo::Sort(OpenList, [](ADaisyReefMapElement* A, ADaisyReefMapElement* B)
		{
			return A->GetF() < B->GetF();
		});

		ADaisyReefMapElement* CurrentList = OpenList[0];

		OpenList.Remove(CurrentList);
		ClosedList.Add(CurrentList);

		if (CurrentList == End)
		{
			UE_LOG(LogPathFinder, Display, TEXT("Finish"));
			
			return GetFinishedList(Start, End);
		}

		for (auto Element : GetNeightbourOverlayTiles(CurrentList->GetActorLocation(), Range))
		{
			if (ClosedList.Contains(Element) || FMath::Abs(CurrentList->GetActorLocation().X - Element->GetActorLocation().X) > 1)
			{
				continue;
			}

			Element->SetG(GetManhattenDistance(Start, Element));
			Element->SetH(GetManhattenDistance(End, Element));

			UE_LOG(LogPathFinder, Display, TEXT("%s, with F: %d"), *Element->GetName(), Element->GetF());

			Element->SetPrevious(CurrentList);

			if (!OpenList.Contains(Element))
			{
				OpenList.Add(Element);
			}
		}
	}
	
	return {};
}

TArray<ADaisyReefMapElement*> UDaisyRefPathFinder::GetNeightbourOverlayTiles(FVector StartLocation, TArray<ADaisyReefMapElement*> InRange)
{
	TArray<ADaisyReefMapElement*> NewElement = {};
	TArray<FHitResult> Hits = {};

	UKismetSystemLibrary::BoxTraceMulti(GetWorld(), StartLocation, StartLocation, FVector(MapProperty.GetDefaultObject()->MapProperties.GridOffset.WidthX, MapProperty.GetDefaultObject()->MapProperties.GridOffset.WidthY, MapProperty.GetDefaultObject()->MapProperties.GridOffset.WidthX), FRotator::ZeroRotator, TraceTypeQuery1, false, {}, EDrawDebugTrace::Persistent, Hits, true);
	
	for (auto Hit : Hits)
	{
		ADaisyReefMapElement* SelectedElement = Cast<ADaisyReefMapElement>(Hit.GetActor());
		if (SelectedElement->IsValidLowLevel())
		{
			if (SelectedElement->GetIsWalkable() && !SelectedElement->GetActorLocation().Equals(StartLocation) && InRange.Contains(SelectedElement))
			{
				NewElement.AddUnique(Cast<ADaisyReefMapElement>(Hit.GetActor()));
			}
		}
	}
	
	return  NewElement;
}

int UDaisyRefPathFinder::GetManhattenDistance(ADaisyReefMapElement* Start, ADaisyReefMapElement* End)
{
	return FMath::Abs(Start->GetActorLocation().X - End->GetActorLocation().X) + FMath::Abs(Start->GetActorLocation().Y - End->GetActorLocation().Y);
}

TArray<ADaisyReefMapElement*> UDaisyRefPathFinder::GetFinishedList(ADaisyReefMapElement* Start, ADaisyReefMapElement* End)
{
	TArray<ADaisyReefMapElement*> FinishedList = {};
	ADaisyReefMapElement* CurrentEnd = End;

	while (CurrentEnd != Start)
	{
		FinishedList.Add(CurrentEnd);
		CurrentEnd = CurrentEnd->GetPrevious();
	}

	Algo::Reverse(FinishedList);

	return FinishedList;
}
