#pragma once
#include "CommonInclude.h"
#include "acEntity.h"
#include "acComponent.h"

namespace ac
{
	class RigidbodyComponent : public Component
	{
	public:
		RigidbodyComponent();
		~RigidbodyComponent();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

		void SetMass(float mass) { mMass = mass; }
		void AddForce(Vector2 force) { mForce = force; }
		void SetGround(bool ground) { mbGround = ground; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		Vector2 GetVelocity() { return mVelocity; }
	private:
		bool mbGround;
		float mMass;
		float mFriction;

		Vector2 mForce;
		Vector2 mAcceleration;
		Vector2 mVelocity;
		Vector2 mLimitVelocity;
		Vector2 mGravity;
	};
}