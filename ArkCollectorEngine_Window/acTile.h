#pragma once
#include "..\\ArkCollectorEngine_SOURCE\\acGameObject.h"

namespace ac
{
	class Tile : public GameObject
	{
	public:
		Tile();
		~Tile();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC InHdc);

		void SetIndexPosition(int idxX, int idxY);
	private:
	};

}
