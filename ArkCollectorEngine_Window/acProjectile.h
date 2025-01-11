#pragma once
#include "..\\ArkCollectorEngine_SOURCE\\acGameObject.h"

namespace ac
{
	/*
		발사체 OR 이펙트
		
		mStartPosirion(발사체 시작 위치)
		mVelocity(발사체 속도)
		mRange(발사체 범위: 시작 위치와 현재 발사체의 위치간의 거리가 발사체 범위 밖이라면 발사체는 사라지도록 함 => 발사체 스크립트에 구체적으로 구현) 
	*/
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
