#include "..\\ArkCollectorEngine_SOURCE\\acGameObject.h"

namespace ac
{
	class Boss : public GameObject
	{
	public:
		Boss();
		~Boss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

	private:

	};

}