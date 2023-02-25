#pragma once
#include "CharacterGameplayAbility.h"

#include "Ability.generated.h"

UCLASS()
class UAbility : public UCharacterGameplayAbility
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
};
