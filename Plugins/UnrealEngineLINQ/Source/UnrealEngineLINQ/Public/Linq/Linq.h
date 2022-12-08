// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Public/Containers/Array.h"
#include "Core/Public/Traits/ElementType.h"

/**
 * 
 */
template<typename InElementType, typename InAllocatorType>
class UNREALENGINELINQ_API Linq
{
	template <typename OtherInElementType, typename OtherAllocator>
	friend class TArray;
	friend class Linq;
	
public:
	Linq();
	~Linq();

public:
	typedef typename InAllocatorType::SizeType SizeType;
	typedef InElementType ElementType;
	typedef InAllocatorType AllocatorType;

public:
	template <typename Predicate>
	TArray<ElementType> Where(Predicate Pred) const
	{
		
	}
};
