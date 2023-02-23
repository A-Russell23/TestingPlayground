#pragma once
#include "Observer.h"

class UGasMonitoringSubsystem : public UGameInstanceSubsystem, public Observer
{
public:
	virtual void onNotify() override;
	
};
