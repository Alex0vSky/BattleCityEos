using UnrealBuildTool;
public class BcEosEditorTarget : TargetRules
{
	public BcEosEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "BcEosCore" } );
		bUsePDBFiles = false;
		WindowsPlatform.bUseBundledDbgHelp = false;
		WindowsPlatform.bCreateHotPatchableImage = false;
		bUseIncrementalLinking = true;
		WindowsPlatform.bOptimizeGlobalData = false;
		bDisableDebugInfo = true;
		// WindowsPlatform.bStripUnreferencedSymbols = true;
		// WindowsPlatform.bMergeIdenticalCOMDATs = true;
	}
}
