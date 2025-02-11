// Nicholas Wile 2025 - Freely use this code for any purpose.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ThirdPersonCharacter.generated.h"

UCLASS()
class CPPSAMPLES_API AThirdPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AThirdPersonCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	FVector StartLocation = FVector(0.f, 0.f, -90.f);

	UPROPERTY(VisibleAnywhere)
	FVector SpawnLocation = FVector(0.f, 0.f, 0.f);

	UPROPERTY(VisibleAnywhere)
	FRotator StartRotation = FRotator(0.f, -90.f, 0.f);

	UPROPERTY(EditAnywhere)
	float MaxSpeed = 1000.f;

	UPROPERTY(EditAnywhere)
	float DefaultSpeed = 600.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool Crouching = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool Jumping = false;

	UFUNCTION()
	void MoveY(float axis);

	UFUNCTION()
	void MoveX(float axis);

	UFUNCTION()
	void StartCrouch();

	UFUNCTION()
	void EndCrouch();

	UFUNCTION()
	void StartSprint();

	UFUNCTION()
	void EndSprint();

	UFUNCTION()
	void StartJump();

	UFUNCTION()
	void EndJump();
};
