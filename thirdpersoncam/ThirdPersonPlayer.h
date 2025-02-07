// Nicholas Wile 2025 - Freely use this code for any purpose.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ThirdPersonPlayer.generated.h"

UCLASS()
class CPPSAMPLES_API AThirdPersonPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AThirdPersonPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* springarm;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* camera;

	UPROPERTY(EditAnywhere)
	FVector location = FVector(0.0f, 0.0f, 50.0f);

	UPROPERTY(EditAnywhere)
	FRotator rotation = FRotator(-60.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere)
	FVector2D armLength = FVector2D(400.f, 300.f);

	UPROPERTY(EditAnywhere)
	bool enableLag = true;

	UPROPERTY(EditAnywhere)
	float lagSpeed = 3.0f;

	UPROPERTY(EditAnywhere)
	FVector2D fovRange = FVector2D(90.f, 60.f);

	UPROPERTY(EditAnywhere)
	FVector2D zoomSpeed = FVector2D(0.5f, 0.25f);

private:
	FVector2D _moveInput = FVector2D(0.f,0.f);
	FVector2D _lookInput = FVector2D(0.f, 0.f);
	float _fovFactor = 90.f;
	bool isZooming = false;

	void MoveX(float axis);
	void MoveY(float axis);
	void CamPitch(float axis); // look up
	void CamYaw(float axis); // look side
	void ZoomIn();
	void ZoomOut();
};
