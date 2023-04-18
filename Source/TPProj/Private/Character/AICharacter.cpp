// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter.h"

#include "Character/Player/DemoPlayerCharacter.h"
#include "AI/PlayerAIController.h"
#include "Player/DemoPlayerState.h"
#include "Player/DemoPlayerController.h"
#include "Character/Abilities/CharacterAbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"

AICharacter::AICharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	//GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//GetMesh()->SetCollisionProfileName(FName("NoCollision"));

	AIControllerClass = APlayerController::StaticClass();

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

void AICharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ADemoPlayerState* PS = GetPlayerState<ADemoPlayerState>();
	if (PS)
	{
		InitializeStartingValues(PS);
		AddStartupEffects();
		AddCharacterAbilities();
	}
}

float AICharacter::GetHealth() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetHealth();
	}

	return 0.0f;
}

float AICharacter::GetMaxHealth() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMaxHealth();
	}

	return 0.0f;
}

void AICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AICharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	ADemoPlayerState* PS = GetPlayerState<ADemoPlayerState>();
	if (PS)
	{
		InitializeStartingValues(PS);
	}
}

void AICharacter::InitializeStartingValues(ADemoPlayerState* PS)
{
	AbilitySystemComponent = Cast<UCharacterAbilitySystemComponent>(PS->GetAbilitySystemComponent());
	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
	AttributeSetBase = PS->GetAttributeSetBase();
	AbilitySystemComponent->SetTagMapCount(DeadTag, 0);
	InitializeAttributes();
	SetHealth(GetMaxHealth());
	SetMana(GetMaxMana());
}
