#pragma once
#include "..\\ArkCollectorEngine_SOURCE\\acGameObject.h"

namespace ac
{
	class Projectile : public GameObject
	{
	public:
		Projectile();
		Projectile(math::Vector2 velocity);
		~Projectile();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

		math::Vector2 GetVelocity() { return mVelocity; }
		void SetVelocity(math::Vector2 velocity) { mVelocity = velocity; }
		float GetRange() { return mRange; }
		void SetRange(float range) { mRange = range; }
		math::Vector2 GetStartPosition() { return mStartPosition; }
		void SetStartPosition(math::Vector2 startPosition) { mStartPosition = startPosition; }

	private:
		math::Vector2 mVelocity;
		float mRange;

		math::Vector2 mStartPosition;
	};
}
