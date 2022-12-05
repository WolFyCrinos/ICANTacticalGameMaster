// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DaisyReefGPESpawner.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent))
class ICANTACTICALGAME_API UDaisyReefGPESpawner : public UPrimitiveComponent
{
	GENERATED_BODY()

public:
	UDaisyReefGPESpawner();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="DaisyReef|SpawnerMesh")
	UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="DaisyReef|SpawnerMesh")
	UStaticMesh* Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="DaisyReef|SpawnerMesh")
	FVector OffsetLocation = {};

	virtual void BeginPlay() override;

	virtual void OnComponentCreated() override;
};
