// Copyright Epic Games, Inc. All Rights Reserved.

#include "Test2Commands.h"

#define LOCTEXT_NAMESPACE "FTest2Module"

void FTest2Commands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "Test2", "Execute Test2 action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
