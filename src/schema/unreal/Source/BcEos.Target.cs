using UnrealBuildTool;
public class BcEosTarget : TargetRules
{
	public BcEosTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "BcEosCore" } );
		bUsePDBFiles = false;
		// WindowsPlatform.bStripUnreferencedSymbols = true;
		// WindowsPlatform.bMergeIdenticalCOMDATs = true;
		WindowsPlatform.bUseBundledDbgHelp = false;
		WindowsPlatform.bOptimizeGlobalData = false;
		WindowsPlatform.bCreateHotPatchableImage = false;
		bUseIncrementalLinking = true;
	}
}
