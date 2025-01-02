#pragma once
#include "acColliderComponent.h"

namespace ac
{
	/* 사용 예시
	* BoxCollidier2DComponent* boxCol = gameObj->AddComponent<BoxCollidier2DComponent>();
	* boxCol->SetSize(math::Vector2::One);
	* boxCol->SetOffset(math::Vector2::Zero);
	*/
	class BoxCollidier2DComponent : public ColliderComponent
	{
	public:
		BoxCollidier2DComponent();
		~BoxCollidier2DComponent();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

	private:
	};
}

