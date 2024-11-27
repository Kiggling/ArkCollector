#pragma once
#include "CommonInclude.h"
#include "acEntity.h"
#include "acComponent.h"

namespace ac
{
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
		math::Vector2 GetPosition() const { return mPosition; }
		math::Vector2 GetRotation() const {	return mRotation; }
		float GetScale() const { return mScale; }

	private:
		math::Vector2 mPosition;
		math::Vector2 mRotation;
		float mScale;

	};
}
