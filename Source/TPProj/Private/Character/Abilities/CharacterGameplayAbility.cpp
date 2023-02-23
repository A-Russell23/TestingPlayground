// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/CharacterGameplayAbility.h"
#include "Character/Abilities/CharacterAbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Plugin/UGasMonitoringSubsystem.h"

UCharacterGameplayAbility::UCharacterGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Dead")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")));

	
	//UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if(GameInstance != nullptr)
	{
		Observer* GasMonitoringSubsystem = GameInstance->GetSubsystem<UGasMonitoringSubsystem>();
		//GasMonitoringSubsystem->doSomething();
		//Observer* test = &(*GasMonitoringSubsystem);
		//test->onNotify();
		addObserver(GasMonitoringSubsystem);
	}
}

void UCharacterGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (ActivateAbilityOnGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}

void UCharacterGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	updateEntity(this->GetName());
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UCharacterGameplayAbility::updateEntity(FString ability)
{
	notify();
	
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Activated : " + ability));	
	
}
