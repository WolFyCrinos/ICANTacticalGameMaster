// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objects/Maps/DaisyReefMapObject.h"
#include "DaisyReefMapElement.generated.h"

UCLASS(BlueprintType, Blueprintable)
class ICANTACTICALGAME_API ADaisyReefMapElement : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADaisyReefMapElement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * @brief 
	 * @param bSetIsWalkable 
	 * @param SetLocation 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual void InitElement(const bool bSetIsWalkable, const FVector SetLocation);

	/**
	 * @brief 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual bool GetIsWalkable();

	/**
	 * @brief 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual FVector GetElementLocation();

	/**
	 * @brief 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual int GetF();

	/**
	 * @brief 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual void SetG(int NewG);

	/**
	 * @brief 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual void SetH(int NewH);

	/**
	 * @brief 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual ADaisyReefMapElement* GetPrevious();

	/**
	 * @brief 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual void SetPrevious(ADaisyReefMapElement* NewPrevious);

private:
	ADaisyReefMapElement* Previous = nullptr;
	bool bIsWalkable;
	FVector Location;
	int G;
	int H;
	int F;
};
