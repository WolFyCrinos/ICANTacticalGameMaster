// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objects/Maps/DaisyReefMapObject.h"
#include "UObject/UnrealTypePrivate.h"
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
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual bool GetIsWalkable();

	/**
	 * @brief 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual void SetIsWalkable(bool SetIsWalkable);

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
	virtual int GetG();

	/**
	 * @brief 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual int GetH();

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
	 * @param NewPrevious 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual void SetPrevious(ADaisyReefMapElement* NewPrevious);

	/**
	 * @brief 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual void FindNeighbour();

	/**
	 * @brief 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual TArray<ADaisyReefMapElement*> GetNeighbour();

	/**
	 * @brief 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual void SetMapProperty(TSubclassOf<UDaisyReefMapObject> NewMapProperty);

	/**
	 * @brief 
	 * @param NewPawn 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual void SetCurrentPawn(APawn* NewPawn);

	/**
	 * @brief 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual APawn* GetCurrentPawn();

	/**
	 * @brief 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual bool HasAnyPawn();
	
private:
	ADaisyReefMapElement* Previous = nullptr;
	TSubclassOf<UDaisyReefMapObject> MapProperty;
	TArray<ADaisyReefMapElement*> Neighbour = {};
	APawn* CurrentPlayer;
 	bool bIsWalkable;
	int G = 0;
	int H = 0;
	int F = 0;
};
