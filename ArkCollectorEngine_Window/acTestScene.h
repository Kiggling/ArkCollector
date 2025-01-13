#pragma once
#include "..\\ArkCollectorEngine_SOURCE\\acScene.h"

namespace ac
{
	class TestScene : public Scene
	{
	public:
		TestScene();
		~TestScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
		
		void OnEnter() override;
		void OnExit() override;
		
	private:
		void mapInit();
		void playerInit();
		void bossInit();
	private:
		class Player* mPlayer;
		class Boss* mBoss;
	};
}
