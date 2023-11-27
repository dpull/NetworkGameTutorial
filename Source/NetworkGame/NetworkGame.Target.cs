using UnrealBuildTool;
using System.Collections.Generic;

public class NetworkGameTarget : TargetRules
{
	public NetworkGameTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "NetworkGame" } );
	}
}
