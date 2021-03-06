// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ActionRPGGameEditor : ModuleRules
{
    public ActionRPGGameEditor(TargetInfo Target)
    {
        PublicDependencyModuleNames.AddRange(new string[] 
		{ 
            "GameplayTags",
            "AssetTools"
		});
        PrivateDependencyModuleNames.AddRange(new string[] 
		{ 
			"ActionRPGGame",
            "MainFrame",
            "Core",
			"CoreUObject",
			"Slate",
			"SlateCore",
			"Engine",
            "InputCore",
			"AssetTools",
			"UnrealEd", // for FAssetEditorManager
			"KismetWidgets",
			"GraphEditor",
			"Kismet",  // for FWorkflowCentricApplication
			"PropertyEditor",
			"RenderCore",
			"LevelEditor", // for EdModes to get a toolkit host  //@TODO: PAPER: Should be a better way to do this (see the @todo in EdModeTileMap.cpp)
			"Paper2D",
			"ContentBrowser",
			"WorkspaceMenuStructure",
			"EditorStyle", 
            "JsonUtilities",
            "ClassViewer",
            "AssetRegistry",
            "ActorPickerMode"
		});

        PrivateIncludePathModuleNames.AddRange(
         new string[] {
				"Settings"
			}
);
    }
}
