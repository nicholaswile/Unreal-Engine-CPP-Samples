// Nicholas Wile 2025 - Freely use this code for any purpose.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ThirdPersonGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CPPSAMPLES_API AThirdPersonGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void StartPlay() override;
	
};
