// This class would have been used to calculate damage for resistances. However this feature did not reach final development.
// Therefore this code is not used in the project, but is included to be worked on in the future.

#include "DamageCalculations/DamageCalcExecution.h"

#include "GameplayEffectExecutionCalculation.h"
#include "Character/Abilities/AttributeSets/CharacterAttributeSetBase.h"

struct FDamageCapture
{
	// Declaration of captured attribute definitions
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance);

	FDamageCapture()
	{
		// Captured attributes definitions
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSetBase, Health, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSetBase, Resistance, Target, false);
	}
};

static const FDamageCapture& DamageCapture()
{
	static FDamageCapture DmgCap;
	return DmgCap;
}

UDamageCalcExecution::UDamageCalcExecution()
{
	RelevantAttributesToCapture.Add(DamageCapture().HealthDef);
	RelevantAttributesToCapture.Add(DamageCapture().ResistanceDef);
}

void UDamageCalcExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.TargetTags = TargetTags;
	EvaluationParameters.SourceTags = SourceTags;

	//Get target resistance
	float Resistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageCapture().ResistanceDef, EvaluationParameters, Resistance);

	float BaseDamage = Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")));
	
	//Damage cal
	float OutDamage = (BaseDamage * Resistance);
	//float Damage = 0.f;

	if(OutDamage < 0.f) //todo - replace with clamp
	{
		OutDamage = 0.f;
	}

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageCapture().HealthProperty, EGameplayModOp::Additive, -OutDamage));
}


