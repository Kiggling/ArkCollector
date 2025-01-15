#pragma once
#include "CommonInclude.h"
#include "acEntity.h"
#include "acComponent.h"

namespace ac
{
	/* 사용 예시
	* TransformComponent* tr = gameObj->AddComponent<TransformComponent>();
	* tr->SetPosition(math::Vector2(1.0f, 1.0f));
	*/
	class TransformComponent : public Component
	{
	public:
		TransformComponent();
		~TransformComponent();

		static math::Vector2 MovementRangeLeftTop;
		static math::Vector2 MovementRangeRightBottom;

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

		void SetPosition(math::Vector2 InPos) { 
			InPos.x = max(InPos.x, MovementRangeLeftTop.x);
			InPos.x = min(InPos.x, MovementRangeRightBottom.x);
			InPos.y = max(InPos.y, MovementRangeLeftTop.y);
			InPos.y = min(InPos.y, MovementRangeRightBottom.y);

			mPosition = InPos; 
		}
		void SetScale(math::Vector2 InScale) { mScale = InScale; }
		void SetRotation(float InRot) { mRotation = InRot; }
		void SetWidth(float InWidth) { mWidth = InWidth; }
		void SetHeight(float InHeight) { mHeight = InHeight; }
		math::Vector2 GetPosition() const { return mPosition; }
		math::Vector2 GetScale() const { return mScale; }
		float GetRotation() const { return mRotation; }
		float GetWidth() const { return mWidth; }
		float GetHeight() const { return mHeight; }

	private:
		math::Vector2 mPosition;
		math::Vector2 mScale;
		float mWidth;
		float mHeight;
		float mRotation;

	};
}
