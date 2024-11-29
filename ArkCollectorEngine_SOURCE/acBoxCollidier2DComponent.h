#pragma once
#include "acColliderComponent.h"

namespace ac
{
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

