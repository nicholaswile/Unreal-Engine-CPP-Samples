// Nicholas Wile 2025 - Freely use this code for any purpose.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "FPSHud.generated.h"

/**
 * 
 */
UCLASS()
class CPPSAMPLES_API AFPSHud : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly) 
	UTexture2D* CrosshairTex;

public:
	virtual void DrawHUD() override;

};
