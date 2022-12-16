// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/DaisyReefMapElement.h"
#include "DaisyRefPathFinder.generated.h"

ICANTACTICALGAME_API DECLARE_LOG_CATEGORY_EXTERN(LogPathFinder, Display, All);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent))
class ICANTACTICALGAME_API UDaisyRefPathFinder : public UPrimitiveComponent
{
	GENERATED_BODY()
	
public:
	UDaisyRefPathFinder();

	/**
	 * @brief
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|TextureMap", meta=(ShowTreeView))
	TSubclassOf<UDaisyReefMapObject> MapProperty;

protected:
	/**
	 * @brief 
	 * @param Start 
	 * @param End 
	 * @param Range 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	void FindPath(ADaisyReefMapElement* Start, ADaisyReefMapElement* End, int Range);

	/**
	 * @brief 
	 * @param Start 
	 * @param End 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	int GetManhattenDistance(ADaisyReefMapElement* Start, ADaisyReefMapElement* End);

	/**
	 * @brief 
	 * @param Start 
	 * @param End 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	TArray<ADaisyReefMapElement*> GetFinishedList(ADaisyReefMapElement* Start, ADaisyReefMapElement* End, int Range);

	/**
	 * @brief 
	 * @param Start 
	 * @param End 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	TArray<ADaisyReefMapElement*> GetPath();

private:
	TArray<ADaisyReefMapElement*> Path = {};
};
