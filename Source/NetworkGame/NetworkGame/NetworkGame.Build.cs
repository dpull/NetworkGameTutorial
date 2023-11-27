using UnrealBuildTool;

public class NetworkGame : ModuleRules
{
	public NetworkGame(ReadOnlyTargetRules Target) : base(Target)
	{
        PrivatePCHHeaderFile = "PrivatePCH.h";
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { });
		PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" , "UMG", "Paper2D" });
	}
}
