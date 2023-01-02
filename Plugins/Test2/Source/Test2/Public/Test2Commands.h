// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "Test2Style.h"

class FTest2Commands : public TCommands<FTest2Commands>
{
public:

	FTest2Commands()
		: TCommands<FTest2Commands>(TEXT("Test2"), NSLOCTEXT("Contexts", "Test2", "Test2 Plugin"), NAME_None, FTest2Style::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
