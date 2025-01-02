#pragma once
#include "acComponent.h"
#include "acTexture.h"

namespace ac
{
	class TilemapRendererComponent : public Component
	{
	public:
		TilemapRendererComponent();
		~TilemapRendererComponent();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void SetTexture(graphics::Texture* texture) { mTexture = texture; }
		void SetSize(math::Vector2 size) { mSize = size; }
		void SetIndex(math::Vector2 index) { mIndex = index; }
		math::Vector2 GetIndex() { return mIndex; }

		static math::Vector2 OriginTileSize;
		static math::Vector2 SelectedIndex;
		static math::Vector2 TileSize;
	private:
		graphics::Texture* mTexture;
		math::Vector2 mSize;
		math::Vector2 mIndex;
		math::Vector2 mTileSize;
	};
}
