// Kill Them All Game, All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class ToKillThemAllEditorTarget : TargetRules
{
	public ToKillThemAllEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ToKillThemAll" } );
	}
}
