// Kill Them All Game, All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class ToKillThemAllTarget : TargetRules
{
	public ToKillThemAllTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ToKillThemAll" } );
	}
}
