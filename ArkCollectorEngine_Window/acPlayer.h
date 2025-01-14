#pragma once
#include "..\\ArkCollectorEngine_SOURCE\\acGameObject.h"

namespace ac
{
	class Player : public GameObject
	{
	public:
		Player();
		~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

	private:

	};

}
