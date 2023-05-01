#include "Character/Abilities/CharacterGameplayAbility.h"
#include "Character/Abilities/CharacterAbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Plugin/UGasMonitoringSubsystem.h"

UCharacterGameplayAbility::UCharacterGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Dead")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")));
	

	//UGasMonitoringSubsystem* GasMonitoringSubsystem = GEngine->GetEngineSubsystem<UGasMonitoringSubsystem>();
	//addObserver(GasMonitoringSubsystem);
	
	
	//UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//UEngine* engine = UGameplayStatics::Get(GetWorld());
	//if(engine != nullptr)
	//{
		//Observer* GasMonitoringSubsystem = GameInstance->GetSubsystem<UGasMonitoringSubsystem>();
		//GasMonitoringSubsystem->doSomething();
		//Observer* test = &(*GasMonitoringSubsystem);
		//test->onNotify();
		
	//}
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
	//UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	//if(GameInstance != nullptr)
	//{
	//	UGasMonitoringSubsystem* GasMonitoringSubsystem = GameInstance->GetSubsystem<UGasMonitoringSubsystem>();
	//	GasMonitoringSubsystem->onNotify();
	//}
	//notify();
	
	
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Activated : " + ability));
	for (auto tag : this->AbilityTags)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Ability has tag : " + tag.ToString()));
	}
}
