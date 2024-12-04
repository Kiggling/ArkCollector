#pragma once
#include "acColliderComponent.h"

namespace ac
{
	/* 사용 예시
	* CircleCollider2DComponent* circleCol = gameObj->AddComponent<CircleCollider2DComponent>();
	* circleCol->SetSize(math::Vector2::One);
	* circleCol->SetOffset(math::Vector2::Zero);
	*/
	class CircleCollider2DComponent : public ColliderComponent
	{
	public:
		CircleCollider2DComponent();
		~CircleCollider2DComponent();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

	private:
	};
}

