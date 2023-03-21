// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TutorialCharacterBase.h"
#include "Player/DemoPlayerState.h"
#include "AICharacter.generated.h"

/**
 * 
 */
UCLASS()
class TPPROJ_API AICharacter : public ATutorialCharacterBase
{
	GENERATED_BODY()

public:
	AICharacter(const FObjectInitializer& ObjectInitializer);

	virtual void PossessedBy(AController* NewController) override;

protected:
	bool ASCInputBound = false;

	FGameplayTag DeadTag;

	virtual void BeginPlay() override;

	virtual void OnRep_PlayerState() override;

	void InitializeStartingValues(ADemoPlayerState* PS);
};
