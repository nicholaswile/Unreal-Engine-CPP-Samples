// Nicholas Wile 2025 - Freely use this code for any purpose.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSProjectile.h"
#include "FPSCharacter.generated.h"

UCLASS()
class CPPSAMPLES_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 100.f;

	UPROPERTY(EditAnywhere)
	FVector2D ZoomSpeed = FVector2D(0.5f, 0.25f);

	UPROPERTY(EditAnywhere)
	FVector SpawnLocation = FVector(0.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere)
	class UCameraComponent* FPSCamera;

	UPROPERTY(EditAnywhere)
	FVector CameraPos = FVector(0.f, 0.f, 50.f + BaseEyeHeight);

	// This will be the "weapons and hands" mesh only visible in FPS
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FPSMesh;

	UFUNCTION()
	void MoveX(float axis);

	UFUNCTION()
	void MoveY(float axis);

	UFUNCTION()
	void CamPitch(float axis); // up/down

	UFUNCTION()
	void CamYaw(float axis); // left/right

	UFUNCTION()
	void CamZoomIn();

	UFUNCTION()
	void CamZoomOut();

	UFUNCTION()
	void JumpStart(); // jump key pressed

	UFUNCTION()
	void JumpEnd(); // jump key released

	UFUNCTION()
	void Fire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset = FVector(100.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere)
	float ProjectilePitch = 10.f;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

private:
	FVector2D _moveInput = FVector2D(0.f, 0.f);
	FVector2D _camInput = FVector2D(0.f, 0.f);

	bool _isZooming = false;
	float _zoomScale = 0.f;
};