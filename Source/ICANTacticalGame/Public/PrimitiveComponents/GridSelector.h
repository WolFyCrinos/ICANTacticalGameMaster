// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "GridSelector.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ICANTACTICALGAME_API UGridSelector : public UPrimitiveComponent
{
	GENERATED_BODY()

public:
	UGridSelector();
	
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DaisyReef|Particle")
	//UNiagaraSystem* GridSelectorFX = nullptr;

protected:
	virtual  void BeginPlay() override;

private:
	//FNiagaraSystemInstanceControllerConstPtr NewNiagaraInstance = nullptr;
};
