// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DaisyReefTeamObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ICANTACTICALGAME_API UDaisyReefTeamObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NameTeam = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor ColorTeam = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* TextureTeam = nullptr;
};
