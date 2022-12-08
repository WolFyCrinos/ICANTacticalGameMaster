// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual void InitElement(const bool bSetIsWalkable, const FVector SetLocation);

	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual bool GetIsWalkable();

	UFUNCTION(BlueprintCallable, Category="DaisyReef")
	virtual FVector GetElementLocation();

private:
	bool bIsWalkable;
	FVector Location;
};
