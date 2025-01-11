#pragma once
#include "acStatComponent.h"

namespace ac
{
	class BossStatComponent : public StatComponent
	{
	public:
		BossStatComponent();
		~BossStatComponent();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

	private:
	};
}
