using UnrealBuildTool;

public class TidesOfTheForsaken : ModuleRules
{
    public TidesOfTheForsaken(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "InputCore" });
    }
}
