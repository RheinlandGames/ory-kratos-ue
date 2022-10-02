// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OryKratos : ModuleRules
{
	public OryKratos(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new[] {
			"Core", "HTTP"
		});
		
		PrivateDependencyModuleNames.AddRange(new[] {
			"CoreUObject",
			"Json",
			"JsonUtilities"
		});
	}
}
