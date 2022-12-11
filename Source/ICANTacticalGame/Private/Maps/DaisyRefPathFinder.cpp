// Fill out your copyright notice in the Description page of Project Settings.


#include "Maps/DaisyRefPathFinder.h"

#include "Algo/RemoveIf.h"


FDaisyRefPathFinder::FDaisyRefPathFinder()
{
	SearchableElement.Empty();
}

FDaisyRefPathFinder::~FDaisyRefPathFinder()
{
	
}

TArray<ADaisyReefMapElement*> FDaisyRefPathFinder::FindPath(ADaisyReefMapElement* Start,
	ADaisyReefMapElement* End, TArray<ADaisyReefMapElement*> Range)
{
	SearchableElement.Empty();

	TArray<ADaisyReefMapElement*> OpenList = {};
	TArray<ADaisyReefMapElement*> ClosedList = {};

	if (!Range.IsEmpty())
	{
		for (auto Element : Range)
		{
			SearchableElement.AddUnique(Element);
		}
	}

	OpenList.AddUnique(Start);
	TArray<ADaisyReefMapElement*> CurrentList = OpenList;

	while (!OpenList.IsEmpty())
	{
		Algo::Sort(CurrentList, [](ADaisyReefMapElement* A, ADaisyReefMapElement* B)
		{
			return A->GetF() < B->GetF();
		});

		OpenList.Remove(CurrentList[0]);
		ClosedList.Add(CurrentList[0]);

		if (CurrentList[0] == End)
		{
			//TO DO
		}

		//TO DO
	}
	
	return {};
}
