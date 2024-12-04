#pragma once
#include "CommonInclude.h"
#include "acEntity.h"
#include "acComponent.h"

namespace ac
{
	class CameraComponent : public Component
	{
	public:
		CameraComponent();
		~CameraComponent();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;
		
		void SetTarget(class GameObject* InTarget) { mTarget = InTarget; }
		math::Vector2 GetPositionInCameraSpace(math::Vector2 InPos);
		math::Vector2 GetPositionInToolScene(math::Vector2 InPos);

	private:
		math::Vector2 mCameraPosition;
		math::Vector2 mResolution;
		class GameObject* mTarget;
	};
}