#include "Character/Player/DemoPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "AI/PlayerAIController.h"
#include "Player/DemoPlayerState.h"
#include "Character/Player/DemoPlayerCharacter.h"
#include "Player/DemoPlayerController.h"
#include "Character/Abilities/CharacterAbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"

ADemoPlayerCharacter::ADemoPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetRelativeLocation(FVector(0,0,70));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(FName("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->FieldOfView = 80.0f;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(FName("NoCollision"));

	AIControllerClass = APlayerController::StaticClass();

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

void ADemoPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADemoPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADemoPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ADemoPlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ADemoPlayerCharacter::LookUpRate);
	PlayerInputComponent->BindAxis("Turn", this, &ADemoPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("TurnRate", this, &ADemoPlayerCharacter::TurnRate);

	BindASCInput();
}

void ADemoPlayerCharacter::PossessedBy(AController* NewController)
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

USpringArmComponent* ADemoPlayerCharacter::GetCameraBoom()
{
	return CameraBoom;
}

UCameraComponent* ADemoPlayerCharacter::GetFollowCamera()
{
	return FollowCamera;
}

float ADemoPlayerCharacter::GetStartingCameraBoomArmLength()
{
	return StartingCameraBoomArmLength;
}

FVector ADemoPlayerCharacter::GetStartingCameraBoomLocation()
{
	return StartingCameraBoomLocation;
}

void ADemoPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	StartingCameraBoomArmLength = CameraBoom->TargetArmLength;
	StartingCameraBoomLocation = CameraBoom->GetRelativeLocation();
}

void ADemoPlayerCharacter::LookUp(float Value)
{
	if (IsAlive())
	{
		AddControllerPitchInput(Value);
	}
}

void ADemoPlayerCharacter::LookUpRate(float Value)
{
	if (IsAlive())
	{
		AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->DeltaTimeSeconds);
	}
}

void ADemoPlayerCharacter::Turn(float Value)
{
	if (IsAlive())
	{
		AddControllerYawInput(Value);
	}
}

void ADemoPlayerCharacter::TurnRate(float Value)
{
	if (IsAlive())
	{
		AddControllerYawInput(Value * BaseTurnRate * GetWorld()->DeltaTimeSeconds);
	}
}

void ADemoPlayerCharacter::MoveForward(float Value)
{
	if (IsAlive())
	{
		AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0, GetControlRotation().Yaw, 0)), Value);
	}
}

void ADemoPlayerCharacter::MoveRight(float Value)
{
	if (IsAlive())
	{
		AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0, GetControlRotation().Yaw, 0)), Value);
	}
}

void ADemoPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	ADemoPlayerState* PS = GetPlayerState<ADemoPlayerState>();
	if (PS)
	{
		InitializeStartingValues(PS);
		BindASCInput();
	}
}

void ADemoPlayerCharacter::InitializeStartingValues(ADemoPlayerState* PS)
{
	AbilitySystemComponent = Cast<UCharacterAbilitySystemComponent>(PS->GetAbilitySystemComponent());
	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
	AttributeSetBase = PS->GetAttributeSetBase();
	AbilitySystemComponent->SetTagMapCount(DeadTag, 0);
	InitializeAttributes();
	SetHealth(GetMaxHealth());
	SetMana(GetMaxMana());
}

void ADemoPlayerCharacter::BindASCInput()
{
	if (!ASCInputBound && AbilitySystemComponent.IsValid() && IsValid(InputComponent))
	{
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"), FString("CancelTarget"), FString("TPProjAbilityID"), static_cast<int32>(TPProjAbilityID::Confirm), static_cast<int32>(TPProjAbilityID::Cancel)));

		ASCInputBound = true;
	}
}
