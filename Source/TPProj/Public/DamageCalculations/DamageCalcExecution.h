// This class would have been used to calculate damage for resistances. However this feature did not reach final development.
// Therefore this code is not used in the project, but is included to be worked on in the future.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DamageCalcExecution.generated.h"

UCLASS()
class TPPROJ_API UDamageCalcExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	
	UDamageCalcExecution();

	// Apply the effect
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
