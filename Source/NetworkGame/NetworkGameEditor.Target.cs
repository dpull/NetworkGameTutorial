using UnrealBuildTool;
using System.Collections.Generic;

public class NetworkGameEditorTarget : TargetRules
{
	public NetworkGameEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "NetworkGame" } );
	}
}
