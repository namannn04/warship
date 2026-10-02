using UnrealBuildTool;
using System.Collections.Generic;

public class TidesOfTheForsakenTarget : TargetRules
{
    public TidesOfTheForsakenTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        ExtraModuleNames.Add("TidesOfTheForsaken");
    }
}
