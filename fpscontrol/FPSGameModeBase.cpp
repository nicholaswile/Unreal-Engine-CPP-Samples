// Nicholas Wile 2025 - Freely use this code for any purpose.


#include "FPSGameModeBase.h"

void AFPSGameModeBase::StartPlay() {
	
	Super::StartPlay();

	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, TEXT("Unreal Niko - FPS Game Mode"));
}