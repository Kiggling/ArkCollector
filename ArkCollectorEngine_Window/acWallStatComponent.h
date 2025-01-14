#pragma once
#include "acStatComponent.h"

namespace ac
{
	class WallStatComponent : public StatComponent
	{
	public:
		WallStatComponent();
		~WallStatComponent();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

	private:

	};
}
