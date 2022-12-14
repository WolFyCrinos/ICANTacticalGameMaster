// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ICANTacticalGameEditorTarget : TargetRules
{
	public ICANTacticalGameEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
		ExtraModuleNames.Add("ICANTacticalGame");
	}
}