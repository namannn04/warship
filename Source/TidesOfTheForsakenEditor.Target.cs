using UnrealBuildTool;
using System.Collections.Generic;

public class TidesOfTheForsakenEditorTarget : TargetRules
{
    public TidesOfTheForsakenEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        ExtraModuleNames.Add("TidesOfTheForsaken");
    }
}
