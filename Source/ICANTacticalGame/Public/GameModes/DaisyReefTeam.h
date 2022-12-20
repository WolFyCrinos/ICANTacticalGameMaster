// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/Team/DaisyReefTeamObject.h"
#include "DaisyReefTeam.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ICANTACTICALGAME_API ADaisyReefTeam : public AInfo
{
	GENERATED_BODY()

public:
	/**
	 * @brief 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Classes, meta=(ShowTreeView))
	TArray<TSubclassOf<UDaisyReefTeamObject>> InGameTeams;

protected:
	virtual void BeginPlay() override;
};
