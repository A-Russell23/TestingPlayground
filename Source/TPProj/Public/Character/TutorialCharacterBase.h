// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemInterface.h"
#include "TPProj/TPProj.h"

#include "TutorialCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, ATutorialCharacterBase*, Character);

UCLASS()
class TPPROJ_API ATutorialCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATutorialCharacterBase(const class FObjectInitializer& ObjectInitializer);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(BlueprintAssignable, Category = "TPProj|Character")
	FCharacterDiedDelegate  OnCharacterDied;

	UFUNCTION(BlueprintCallable, Category = "TPProj|Character")
	virtual bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "TPProj|Character")
	virtual int32 GetAbilityLevel(TPProjAbilityID AbilityID) const;

	virtual void RemoveCharacterAbilities();

	virtual void Die();

	UFUNCTION(BlueprintCallable, Category = "TPProj|Character")
	virtual void FinishDying();

	UFUNCTION(BlueprintCallable, Category = "TPProj|Character|Attributes")
	float GetCharacterLevel() const;

	UFUNCTION(BlueprintCallable, Category = "TPProj|Character|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "TPProj|Character|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "TPProj|Character|Attributes")
	float GetMana() const;

	UFUNCTION(BlueprintCallable, Category = "TPProj|Character|Attributes")
	float GetMaxMana() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TWeakObjectPtr<class UCharacterAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<class UCharacterAttributeSetBase> AttributeSetBase;

	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "TPProj|Character")
	FText CharacterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TPProj|Animation")
	UAnimMontage* DeathMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "TPProj|Abilites")
	TArray<TSubclassOf<class UCharacterGameplayAbility>> CharacterAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "TPProj|Abilites")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "TPProj|Abilites")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	virtual void AddCharacterAbilities();

	virtual void InitializeAttributes();

	virtual void AddStartupEffects();


	virtual void SetHealth(float Health);

	virtual void SetMana(float Mana);

};
