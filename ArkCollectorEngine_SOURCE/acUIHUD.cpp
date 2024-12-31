#include "acUIHUD.h"
#include "acResources.h"

ac::UIHUD::UIHUD()
	: UIBase(enums::EUIType::HUD)
{
}

ac::UIHUD::~UIHUD()
{
}

void ac::UIHUD::OnInit()
{
	mTexture = Resources::Find<graphics::Texture>(L"HPBAR");
}

void ac::UIHUD::OnActive()
{
}

void ac::UIHUD::OnInActive()
{
}

void ac::UIHUD::OnUpdate()
{
}

void ac::UIHUD::OnLateUpdate()
{
}

void ac::UIHUD::OnRender(HDC InHdc)
{
	if (mTexture == nullptr)
		assert(false);

	if (mTexture->GetTextureType()
		== graphics::Texture::eTextureType::Bmp)
	{
		if (mTexture->IsAlpha())
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = 255; // 0(transparent) ~ 255(Opaque)

			AlphaBlend(InHdc
				, 0
				, 0
				, mTexture->GetWidth()
				, mTexture->GetHeight()
				, mTexture->GetHdc()
				, 0, 0
				, mTexture->GetWidth()
				, mTexture->GetHeight()
				, func);
		}
		else
		{
			TransparentBlt(InHdc
				, 0
				, 0
				, mTexture->GetWidth()
				, mTexture->GetHeight()
				, mTexture->GetHdc()
				, 0, 0
				, mTexture->GetWidth()
				, mTexture->GetHeight()
				, RGB(255, 0, 255));
		}
	}
	else if (mTexture->GetTextureType()
		== graphics::Texture::eTextureType::Png)
	{
		// 투명화시킬 픽셀의 색 범위
		Gdiplus::ImageAttributes imgAtt = {};
		imgAtt.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));

		Gdiplus::Graphics graphics(InHdc);

		graphics.DrawImage(mTexture->GetImage()
			, Gdiplus::Rect
			(
				0, 0
				, mTexture->GetWidth()
				, mTexture->GetHeight()
			)
			, 0, 0
			, mTexture->GetWidth(), mTexture->GetHeight()
			, Gdiplus::UnitPixel
			, nullptr/*&imgAtt*/);
	}
}

void ac::UIHUD::OnClear()
{
}
