// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class UNREAL_TUTORIAL_2_4EditorTarget : TargetRules
{
	public UNREAL_TUTORIAL_2_4EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("UNREAL_TUTORIAL_2_4");
	}
}
