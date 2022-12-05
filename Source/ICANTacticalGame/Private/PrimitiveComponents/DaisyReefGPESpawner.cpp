// Fill out your copyright notice in the Description page of Project Settings.

#include "PrimitiveComponents/DaisyReefGPESpawner.h"

UDaisyReefGPESpawner::UDaisyReefGPESpawner()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnerMesh"));
	MeshComponent->SetupAttachment(this);
	MeshComponent->SetRelativeTransform(FTransform(FRotator::ZeroRotator, FVector::ZeroVector + OffsetLocation, FVector::OneVector));
}

void UDaisyReefGPESpawner::BeginPlay()
{
	Super::BeginPlay();

	if (MeshComponent->GetAttachParent() != this)
	{
		MeshComponent->SetupAttachment(this);
	}
	
	MeshComponent->SetRelativeTransform(FTransform(FRotator::ZeroRotator, FVector::ZeroVector + OffsetLocation, FVector::OneVector));
}

void UDaisyReefGPESpawner::OnComponentCreated()
{
	Super::OnComponentCreated();

	if (Mesh != nullptr)
	{
		MeshComponent->SetStaticMesh(Mesh);
	}
}
