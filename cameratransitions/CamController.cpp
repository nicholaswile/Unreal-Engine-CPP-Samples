// Nicholas Wile 2025 - Freely use this code for any purpose.

// Custom class
#include "CamController.h"

// Unreal classes
#include "Kismet/GameplayStatics.h"

// Sets default values
ACamController::ACamController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_currentCam = 0;
	_timeRemaining = 2.0f;//Cams[_currentCam].TimeBetweenChanges;
}

// Called when the game starts or when spawned
void ACamController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACamController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_timeRemaining -= DeltaTime;

	if (_timeRemaining <= 0.0f) {
		_timeRemaining += Cams[_currentCam].TimeBetweenChanges;

		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Time Remaining: %f secs"), _timeRemaining));		
		}

		APlayerController* _playerController = UGameplayStatics::GetPlayerController(this, 0);
		
		if (_playerController) {

			if (Cams.Num() > 0) {

				int nextCamIndex = (_currentCam + 1) % Cams.Num();
				AActor* NextCam = Cams[nextCamIndex].Cam;

				if ((_playerController->GetViewTarget() != NextCam && NextCam != nullptr)) {
					_playerController->SetViewTargetWithBlend(NextCam, SmoothBlendTime);

					_currentCam++;
					if (_currentCam >= Cams.Num())
						_currentCam = 0;
				}
			
			}
			
			else {
				if (GEngine) {
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("No cameras to cycle thru")));
				}
			}
		}

		else {
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("No player controller found")));
			}
		}
		
	}
}