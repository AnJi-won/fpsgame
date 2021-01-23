// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAimHUD.h"
#include "Engine/Canvas.h"

AFPSAimHUD::AFPSAimHUD()
{

}

void AFPSAimHUD::DrawHUD()
{
	Super::DrawHUD();

	if (AimTexture)
	{
		// ĵ���� �߽��� ã���ϴ�.
		FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
		// �ؽ�ó �߽��� ĵ���� �߽ɿ� �µ��� �ؽ�ó�� ũ�� ���� ��ŭ �������� �ݴϴ�.
		FVector2D AimDrawPosition(Center.X - (AimTexture->GetSurfaceWidth() * 0.5f), Center.Y - (AimTexture->GetSurfaceHeight() * 0.5f));
		// �߽����� ���ؼ��� �׸��ϴ�.
		FCanvasTileItem TileItem(AimDrawPosition, AimTexture->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);
	}
}