// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/DaisyReefMapElement.h"

/**
 * 
 */
class ICANTACTICALGAME_API FDaisyRefPathFinder
{
public:
	FDaisyRefPathFinder();
	~FDaisyRefPathFinder();

protected:
	/**
	 * @brief 
	 */
	TArray<ADaisyReefMapElement*> SearchableElement;

	/**
	 * @brief 
	 * @param Start 
	 * @param End 
	 * @param Range 
	 * @return 
	 */
	TArray<ADaisyReefMapElement*> FindPath(ADaisyReefMapElement* Start, ADaisyReefMapElement* End, TArray<ADaisyReefMapElement*> Range);
};
