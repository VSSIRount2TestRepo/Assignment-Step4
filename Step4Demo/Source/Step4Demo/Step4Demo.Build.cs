// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Step4Demo : ModuleRules
{
	public Step4Demo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HTTP" });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicAdditionalLibraries.Add("C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64/WS2_32.Lib");


        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
