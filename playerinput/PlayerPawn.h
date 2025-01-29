// Nicholas Wile 2025 - Freely use this code for any purpose.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class CPPSAMPLES_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	UPROPERTY(EditAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere)
	FVector Location = FVector(-250.f, 0.f, 250.f);

	UPROPERTY(EditAnywhere)
	FRotator Rotation = FRotator(-45.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere)
	float Speed = 100.f;

private:
	// Input functions
	void MoveXaxis(float f);
	void MoveYaxis(float f);
	void StartGrow();
	void StopGrow();

	// Input variables
	FVector _velocity = FVector(0.0f, 0.0f, 0.0f);
	bool _bGrowing = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
