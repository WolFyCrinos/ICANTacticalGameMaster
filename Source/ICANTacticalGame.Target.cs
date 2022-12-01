// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ICANTacticalGameTarget : TargetRules
{
	public ICANTacticalGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
		ExtraModuleNames.Add("ICANTacticalGame");
	}
}