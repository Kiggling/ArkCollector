#pragma once
#include "..\\ArkCollectorEngine_SOURCE\acScriptComponent.h"

namespace ac
{
	class PlayerScriptComponent : public ScriptComponent
	{
	public:
		PlayerScriptComponent();
		~PlayerScriptComponent();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

	private:
	};
}

