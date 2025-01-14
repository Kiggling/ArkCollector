#include "..\\ArkCollectorEngine_SOURCE\\acGameObject.h"

namespace ac
{
	class Wall : public GameObject
	{
	public:
		enum class eDirection
		{
			Down,
			Up,
			Left,
			Right,
			None,
			End,
		};

		Wall();
		~Wall();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

		void SetDirection(eDirection InDir) { mDirection = InDir; };
		eDirection GetDirection() { return mDirection; };

	private:
		eDirection mDirection;
	};

}
