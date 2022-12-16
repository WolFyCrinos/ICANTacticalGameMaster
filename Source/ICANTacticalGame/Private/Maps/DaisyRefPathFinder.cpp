// Fill out your copyright notice in the Description page of Project Settings.

#include "Maps/DaisyRefPathFinder.h"

DEFINE_LOG_CATEGORY(LogPathFinder);

UDaisyRefPathFinder::UDaisyRefPathFinder()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDaisyRefPathFinder::FindPath(ADaisyReefMapElement* Start,
	ADaisyReefMapElement* End, int Range)
{
	UE_LOG(LogPathFinder, Display, TEXT("Start: %s, End: %s"), *Start->GetName(), *End->GetName());
	
	TArray<ADaisyReefMapElement*> OpenList = {};
	TArray<ADaisyReefMapElement*> ClosedList = {};

	OpenList.AddUnique(Start);

	while (OpenList.Num() > 0)
	{
		ADaisyReefMapElement* FirstMapElement = OpenList[0];
		
		for (int i = 1; i < OpenList.Num(); i++)
		{
			if (OpenList[i]->GetF() < FirstMapElement->GetF() || OpenList[i]->GetF() == FirstMapElement->GetF())
			{
				if (OpenList[i]->GetH() < FirstMapElement->GetH())
				{
					UE_LOG(LogPathFinder, Display, TEXT("%s, with F: %d"), *OpenList[i]->GetName(), OpenList[i]->GetF());

					FirstMapElement = OpenList[i];
				}
			}
		}

		OpenList.Remove(FirstMapElement);
		ClosedList.Add(FirstMapElement);

		if (FirstMapElement == End)
		{
			Path = GetFinishedList(Start, End, Range);
			return;
		}

		for (auto Neighbour : FirstMapElement->GetNeighbour())
		{
			if (ClosedList.Contains(Neighbour))
			{
				continue;
			}
			
			int NewCostToNeighbour = Neighbour->GetG() + GetManhattenDistance(FirstMapElement, Neighbour);
			
			if (NewCostToNeighbour < Neighbour->GetG() || !OpenList.Contains(Neighbour))
			{
				Neighbour->SetG(NewCostToNeighbour);
				Neighbour->SetH(GetManhattenDistance(Neighbour, End));
				Neighbour->SetPrevious(FirstMapElement);

				UE_LOG(LogPathFinder, Display, TEXT("%s, with G: %d & H: %d"), *Neighbour->GetName(), Neighbour->GetG(), Neighbour->GetH());
				
				if (!OpenList.Contains(Neighbour))
				{
					OpenList.Add(Neighbour);
				}
			}
		}
	}
}

int UDaisyRefPathFinder::GetManhattenDistance(ADaisyReefMapElement* Start, ADaisyReefMapElement* End)
{
	return FMath::Abs(Start->GetActorLocation().X - End->GetActorLocation().X) + FMath::Abs(Start->GetActorLocation().Y - End->GetActorLocation().Y);
}

TArray<ADaisyReefMapElement*> UDaisyRefPathFinder::GetFinishedList(ADaisyReefMapElement* Start, ADaisyReefMapElement* End, int Range)
{
	TArray<ADaisyReefMapElement*> FinishedList = {};
	TArray<ADaisyReefMapElement*> FirstList = {};
	ADaisyReefMapElement* CurrentEnd = End;

	while (CurrentEnd != Start)
	{
		FirstList.Add(CurrentEnd);
		CurrentEnd = CurrentEnd->GetPrevious();
	}

	Algo::Reverse(FirstList);

	for (int i = 0; i < (Range > FirstList.Num() ? FirstList.Num() : Range); i++)
	{
		FinishedList.AddUnique(FirstList[i]);
	}
	
	return FinishedList;
}

TArray<ADaisyReefMapElement*> UDaisyRefPathFinder::GetPath()
{
	return Path;
}
