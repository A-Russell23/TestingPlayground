#include "DemoAssetManager.h"
#include "AbilitySystemGlobals.h"

void UDemoAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
}