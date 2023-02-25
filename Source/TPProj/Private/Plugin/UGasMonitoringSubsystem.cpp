#include "Plugin/UGasMonitoringSubsystem.h"

#include "Engine/Engine.h"

void UGasMonitoringSubsystem::onNotify()
{
	//do something

	//Ability has been activated
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));	
}

void UGasMonitoringSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGasMonitoringSubsystem::Deinitialize()
{
	Super::Deinitialize();
}
