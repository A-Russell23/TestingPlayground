#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "DemoAssetManager.generated.h"

UCLASS()
class TPPROJ_API UDemoAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	virtual void StartInitialLoading() override;
	
};
