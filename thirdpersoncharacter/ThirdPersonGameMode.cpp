// Nicholas Wile 2025 - Freely use this code for any purpose.


#include "ThirdPersonGameMode.h"

void AThirdPersonGameMode::StartPlay() {
	
	Super::StartPlay();
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Unreal Niko - Third Person Game Mode"));
}