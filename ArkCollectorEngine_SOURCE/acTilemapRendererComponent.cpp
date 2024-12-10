#include "acTilemapRendererComponent.h"
#include "acGameObject.h"
#include "acTransformComponent.h"
#include "acRenderer.h"

namespace ac
{
	math::Vector2 TilemapRendererComponent::OriginTileSize = math::Vector2(32.f, 32.f);
	math::Vector2 TilemapRendererComponent::SelectedIndex = math::Vector2::Zero;
	math::Vector2 TilemapRendererComponent::TileSize = math::Vector2(30.f, 30.f);

	TilemapRendererComponent::TilemapRendererComponent()
		: Component(enums::EComponentType::SpriteRenderer)
		, mTexture(nullptr)
		, mSize(math::Vector2::One)
		, mIndex(math::Vector2::Zero)
		, mTileSize(math::Vector2(32.f, 32.f))
	{
		//TileSize = mTileSize * mSize;
	}
	TilemapRendererComponent::~TilemapRendererComponent()
	{
	}
	void TilemapRendererComponent::Initialize()
	{
	}
	void TilemapRendererComponent::Update()
	{
	}
	void TilemapRendererComponent::LateUpdate()
	{
	}
	void TilemapRendererComponent::Render(HDC hdc)
	{
		if (mTexture == nullptr)
			assert(false);

		TransformComponent* tr = GetOwner()->GetComponent<TransformComponent>();
		math::Vector2 pos = tr->GetPosition();
		math::Vector2 scale = tr->GetScale();
		float rot = tr->GetRotation();

		pos = renderer::mainCamera->GetPositionInCameraSpace(pos);

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

				AlphaBlend(hdc
					, pos.x
					, pos.y
					, TileSize.x * scale.x
					, TileSize.y * scale.y
					, mTexture->GetHdc()
					, mIndex.x * mTileSize.x 
					, mIndex.y * mTileSize.y
					, mTileSize.x
					, mTileSize.y
					, func);
			}
			else
			{
				TransparentBlt(hdc
					, pos.x
					, pos.y
					, TileSize.x * scale.x
					, TileSize.y * scale.y
					, mTexture->GetHdc()
					, mIndex.x * mTileSize.x
					, mIndex.y * mTileSize.y
					, mTileSize.x
					, mTileSize.y
					, RGB(255, 0, 255));
			}
		}
		else if (mTexture->GetTextureType()
			== graphics::Texture::eTextureType::Png)
		{
			// 투명화시킬 픽셀의 색 범위
			Gdiplus::ImageAttributes imgAtt = {};
			imgAtt.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));

			Gdiplus::Graphics graphics(hdc);

			//graphics.TranslateTransform(pos.x, pos.y);
			//graphics.RotateTransform(rot);
			//graphics.TranslateTransform(-pos.x, -pos.y);

			graphics.DrawImage(mTexture->GetImage()
				, Gdiplus::Rect
				(
					pos.x, pos.y
					, TileSize.x * scale.x
					, TileSize.y * scale.y
				)
				, mIndex.x * mTileSize.x
				, mIndex.y * mTileSize.y
				, mTileSize.x
				, mTileSize.y
				, Gdiplus::UnitPixel
				, nullptr/*&imgAtt*/);
		}
	}
}