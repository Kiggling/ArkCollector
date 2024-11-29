#include "acRigidbodyComponent.h"
#include "acGameObject.h"
#include "acTransformComponent.h"
#include "acTime.h"

namespace ac
{
	using namespace math;

	RigidbodyComponent::RigidbodyComponent()
		: Component(enums::EComponentType::Rigidbody)
		, mbGround(false)
		, mMass(1.f)
		, mFriction(10.f)
		, mForce(Vector2::Zero)
		, mVelocity(Vector2::Zero)
		, mLimitVelocity(Vector2(200.f, 1000.f))
		, mAcceleration(Vector2::Zero)
		, mGravity(Vector2(0.f, 800.f))
	{
	}
	RigidbodyComponent::~RigidbodyComponent()
	{
	}
	void RigidbodyComponent::Initialize()
	{
	}
	void RigidbodyComponent::Update()
	{
		// F = ma -> a = F/m
		mAcceleration = mForce / mMass;

		mVelocity += mAcceleration * Time::DeltaTime();

		if (mbGround)
		{
			// 땅에 맞닿아 있을 때
			Vector2 gravity = mGravity;
			gravity.normalize();

			float dot = Vector2::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			// 공중에 있을 때
			mVelocity += mGravity * Time::DeltaTime();
		}

		// 최대 속도 제한
		Vector2 gravity = mGravity;
		gravity.normalize();
		float dot = Vector2::Dot(mVelocity, gravity);
		gravity = gravity * dot;

		Vector2 sideVelocity = mVelocity - gravity;
		if (mLimitVelocity.y < gravity.length())
		{
			gravity.normalize();
			gravity *= mLimitVelocity.y;
		}
		if (mLimitVelocity.x < sideVelocity.length())
		{
			sideVelocity.normalize();
			sideVelocity *= mLimitVelocity.x;
		}
		mVelocity = gravity + sideVelocity;

		if (!(mVelocity == Vector2::Zero))
		{
			// 속도에 반대 방향으로 마찰력 적용.
			Vector2 friction = -mVelocity;
			friction = friction.normalize() * mFriction * mMass * Time::DeltaTime();

			// 마찰력으로 인한 속도 감소량이 현재 속도보다 큰 경우.
			if (mVelocity.length() <= friction.length())
			{
				// 멈춤.
				mVelocity = Vector2::Zero;
			}
			else
			{
				mVelocity += friction;
			}

			TransformComponent* tr = GetOwner()->GetComponent<TransformComponent>();
			Vector2 pos = tr->GetPosition();
			pos = pos + mVelocity * Time::DeltaTime();
			tr->SetPosition(pos);

			mForce.clear();

		}
	}
	void RigidbodyComponent::LateUpdate()
	{
	}
	void RigidbodyComponent::Render(HDC InHdc)
	{
	}
}