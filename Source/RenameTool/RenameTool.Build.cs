// Copyright (c) 2024, LJason. All rights reserved.

using UnrealBuildTool;

public class RenameTool : ModuleRules
{
	public RenameTool(ReadOnlyTargetRules target) : base(target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
				"UMG",
				"Blutility"
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"UMGEditor",
				"UnrealEd",
				"ScriptableEditorWidgets",
				"ToolMenus"
			}
		);
	}
}