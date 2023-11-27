using UnrealBuildTool;
using System.Collections.Generic;

public class NetworkGameServerTarget : TargetRules
{
	public NetworkGameServerTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "NetworkGame" } );
	}
}
