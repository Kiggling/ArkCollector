#pragma once
#include "acColliderComponent.h"

namespace ac
{
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

