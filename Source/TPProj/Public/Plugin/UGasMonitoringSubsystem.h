#pragma once
#include "Observer.h"
#include "Subsystems/EngineSubsystem.h"

class UGasMonitoringSubsystem : public UEngineSubsystem, public Observer
{
public:
	virtual void onNotify() override;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
};
