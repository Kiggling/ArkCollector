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

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

		void SetPosition(math::Vector2 InPos) { mPosition = InPos; }
		void SetRotation(math::Vector2 InRot) { mRotation = InRot; }
		void SetScale(float InScale) { mScale = InScale; }
		void SetWidth(float InWidth) { mWidth = InWidth; }
		void SetHeight(float InHeight) { mHeight = InHeight; }
		math::Vector2 GetPosition() const { return mPosition; }
		math::Vector2 GetRotation() const {	return mRotation; }
		float GetScale() const { return mScale; }
		float GetWidth() const { return mWidth; }
		float GetHeight() const { return mHeight; }

	private:
		math::Vector2 mPosition;
		math::Vector2 mRotation;
		float mWidth;
		float mHeight;
		float mScale;

	};
}
