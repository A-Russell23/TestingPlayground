#include "Plugin/UGasMonitoringSubsystem.h"

void UGasMonitoringSubsystem::onNotify()
{
	//do something

	//Ability has been activated
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));	
}
