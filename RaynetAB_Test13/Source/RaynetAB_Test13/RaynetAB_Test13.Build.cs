// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class RaynetAB_Test13 : ModuleRules
{
	public RaynetAB_Test13(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "OnlineSubsystem" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        //Uncomment if you are using online features
        //PrivateDependencyModuleNames.Add("OnlineSubsystem");
        //if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
        //{
        // DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
        // }
    }
}
