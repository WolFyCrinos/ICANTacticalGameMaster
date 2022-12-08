// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AStarGridPathFadingRuntime/Public/AStarGridBasedPathFinder/AStarGridBasedPathFinder.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAStarGridBasedPathFinder() {}
// Cross Module References
	ASTARGRIDPATHFADINGRUNTIME_API UClass* Z_Construct_UClass_AAStarGridBasedPathFinder();
	ASTARGRIDPATHFADINGRUNTIME_API UClass* Z_Construct_UClass_AAStarGridBasedPathFinder_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_AStarGridPathFadingRuntime();
// End Cross Module References
	void AAStarGridBasedPathFinder::StaticRegisterNativesAAStarGridBasedPathFinder()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AAStarGridBasedPathFinder);
	UClass* Z_Construct_UClass_AAStarGridBasedPathFinder_NoRegister()
	{
		return AAStarGridBasedPathFinder::StaticClass();
	}
	struct Z_Construct_UClass_AAStarGridBasedPathFinder_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AAStarGridBasedPathFinder_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_AStarGridPathFadingRuntime,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAStarGridBasedPathFinder_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "AStarGridBasedPathFinder/AStarGridBasedPathFinder.h" },
		{ "ModuleRelativePath", "Public/AStarGridBasedPathFinder/AStarGridBasedPathFinder.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AAStarGridBasedPathFinder_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAStarGridBasedPathFinder>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AAStarGridBasedPathFinder_Statics::ClassParams = {
		&AAStarGridBasedPathFinder::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AAStarGridBasedPathFinder_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AAStarGridBasedPathFinder_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AAStarGridBasedPathFinder()
	{
		if (!Z_Registration_Info_UClass_AAStarGridBasedPathFinder.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AAStarGridBasedPathFinder.OuterSingleton, Z_Construct_UClass_AAStarGridBasedPathFinder_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AAStarGridBasedPathFinder.OuterSingleton;
	}
	template<> ASTARGRIDPATHFADINGRUNTIME_API UClass* StaticClass<AAStarGridBasedPathFinder>()
	{
		return AAStarGridBasedPathFinder::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AAStarGridBasedPathFinder);
	AAStarGridBasedPathFinder::~AAStarGridBasedPathFinder() {}
	struct Z_CompiledInDeferFile_FID_Users_franc_GitHub_ICANTacticalGameMaster_Plugins_GameFeatures_AStarGridPathFading_Source_AStarGridPathFadingRuntime_Public_AStarGridBasedPathFinder_AStarGridBasedPathFinder_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_franc_GitHub_ICANTacticalGameMaster_Plugins_GameFeatures_AStarGridPathFading_Source_AStarGridPathFadingRuntime_Public_AStarGridBasedPathFinder_AStarGridBasedPathFinder_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AAStarGridBasedPathFinder, AAStarGridBasedPathFinder::StaticClass, TEXT("AAStarGridBasedPathFinder"), &Z_Registration_Info_UClass_AAStarGridBasedPathFinder, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AAStarGridBasedPathFinder), 3041336787U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_franc_GitHub_ICANTacticalGameMaster_Plugins_GameFeatures_AStarGridPathFading_Source_AStarGridPathFadingRuntime_Public_AStarGridBasedPathFinder_AStarGridBasedPathFinder_h_3491405073(TEXT("/Script/AStarGridPathFadingRuntime"),
		Z_CompiledInDeferFile_FID_Users_franc_GitHub_ICANTacticalGameMaster_Plugins_GameFeatures_AStarGridPathFading_Source_AStarGridPathFadingRuntime_Public_AStarGridBasedPathFinder_AStarGridBasedPathFinder_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_franc_GitHub_ICANTacticalGameMaster_Plugins_GameFeatures_AStarGridPathFading_Source_AStarGridPathFadingRuntime_Public_AStarGridBasedPathFinder_AStarGridBasedPathFinder_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
