// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/DaisyReefMapElement.h"
#include "GameFramework/Actor.h"
#include "DaisyReefGameMap.generated.h"

class UDaisyReefMapObject;

UCLASS(Blueprintable, BlueprintType)
class ICANTACTICALGAME_API ADaisyReefGameMap : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADaisyReefGameMap();

private:
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
