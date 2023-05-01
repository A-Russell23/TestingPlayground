#pragma once

#include "CoreMinimal.h"
#include "Character/DemoCharacterBase.h"
#include "Player/DemoPlayerState.h"
#include "DemoPlayerCharacter.generated.h"

UCLASS()
class TPPROJ_API ADemoPlayerCharacter : public ADemoCharacterBase
{
	GENERATED_BODY()

public:
	ADemoPlayerCharacter(const FObjectInitializer& ObjectInitializer);
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	class USpringArmComponent* GetCameraBoom();

	class UCameraComponent* GetFollowCamera();

	UFUNCTION(BlueprintCallable, Category = "Demo|Camera")
	float GetStartingCameraBoomArmLength();

	UFUNCTION(BlueprintCallable, Category = "Demo|Camera")
	FVector GetStartingCameraBoomLocation();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Demo|Camera")
	float BaseTurnRate = 45.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Demo|Camera")
	float BaseLookUpRate = 45.0f;

	UPROPERTY(BlueprintReadOnly, category = "Demo|Camera")
	float StartingCameraBoomArmLength;

	UPROPERTY(BlueprintReadOnly, category = "Demo|Camera")
	FVector StartingCameraBoomLocation;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, category = "Demo|Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadOnly, category = "Demo|Camera")
	UCameraComponent* FollowCamera;

	bool ASCInputBound = false;

	FGameplayTag DeadTag;

	virtual void BeginPlay() override;

	void LookUp(float Value);

	void LookUpRate(float Value);

	void Turn(float Value);

	void TurnRate(float Value);

	void MoveForward(float Value);

	void MoveRight(float Value);

	virtual void OnRep_PlayerState() override;

	void InitializeStartingValues(ADemoPlayerState* PS);

	void BindASCInput();
};
