#pragma once
#include "..\\ArkCollectorEngine_SOURCE\\\acScene.h"

namespace ac
{
	class ToolmapScene : public Scene
	{
	public:
		ToolmapScene();
		~ToolmapScene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		virtual void OnEnter();
		virtual void OnExit();

	private:
		std::vector<Layer*> mLayers;
	};
}
