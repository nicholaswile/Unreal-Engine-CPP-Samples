// Nicholas Wile 2025 - Freely use this code for any purpose.


#include "FPSHud.h"

void AFPSHud::DrawHUD() {
	Super::DrawHUD();

	if (CrosshairTex) {
		// Center of canvas
		FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

		// Offset to the center of the tex
		FVector2D CrossHairDrawPosition(Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f));

		// Draw at center
		FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTex->GetResource(), FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);
	}
}