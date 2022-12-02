// Fill out your copyright notice in the Description page of Project Settings.

#include "PrimitiveComponents/GridSelector.h"
//#include "NiagaraFunctionLibrary.h"

UGridSelector::UGridSelector()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGridSelector::BeginPlay()
{
	Super::BeginPlay();

	/*const UNiagaraComponent* FXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),
							GridSelectorFX, FVector::ZeroVector, FRotator::ZeroRotator,
							FVector::OneVector, true, true, ENCPoolMethod::AutoRelease, true);

	FXComponent->AutoAttachParent;

	NewNiagaraInstance = FXComponent->GetSystemInstanceController();
	NewNiagaraInstance->GetSoloSystemInstance()->Activate();*/
}
