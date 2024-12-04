#pragma once
#include "..\\ArkCollectorEngine_SOURCE\\acScene.h"

namespace ac
{
	class ToolScene : public Scene
	{
	public:
		ToolScene();
		~ToolScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void OnEnter() override;
		void OnExit() override;

	private:
	};
}
