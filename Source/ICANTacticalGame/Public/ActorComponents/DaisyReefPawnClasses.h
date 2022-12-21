// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Objects/Team/DaisyReefTeamObject.h"
#include "DaisyReefPawnClasses.generated.h"


UCLASS(ClassGroup=(DaisyReef), meta=(BlueprintSpawnableComponent))
class ICANTACTICALGAME_API UDaisyReefPawnClasses : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDaisyReefPawnClasses();

	/**
	 * @brief 
	 * @param NewTeam 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef|PawnClasses")
	virtual void SetPawnTeam(UDaisyReefTeamObject* NewTeam);

	/**
	 * @brief 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef|PawnClasses")
	virtual UDaisyReefTeamObject* GetPawnTeam();

	/**
	 * @brief 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="DaisyReef|PawnClasses")
	virtual bool PawnHasTeam();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UDaisyReefTeamObject* PawnTeam;
};
