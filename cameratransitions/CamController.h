// Nicholas Wile 2025 - Freely use this code for any purpose.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CamController.generated.h"

USTRUCT()
struct FTransitionCams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	AActor* Cam;

	UPROPERTY(EditAnywhere)
	float TimeBetweenChanges;
};

UCLASS()
class CPPSAMPLES_API ACamController : public AActor
{
	GENERATED_BODY()

private:
	float _timeRemaining;
	int _currentCam;

public:	
	// Sets default values for this actor's properties
	ACamController();

	/*UPROPERTY(EditAnywhere)
	TArray<AActor*> Cams;*/

	UPROPERTY(EditAnywhere)
	TArray<FTransitionCams> Cams;

	/*UPROPERTY(EditAnywhere)
	float DefaultTimeBetweenChanges = 2.0f;*/

	UPROPERTY(EditAnywhere)
	float SmoothBlendTime = 0.75f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};