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
			// ���� �´�� ���� ��
			Vector2 gravity = mGravity;
			gravity.normalize();

			float dot = Vector2::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			// ���߿� ���� ��
			mVelocity += mGravity * Time::DeltaTime();
		}

		// �ִ� �ӵ� ����
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
			// �ӵ��� �ݴ� �������� ������ ����.
			Vector2 friction = -mVelocity;
			friction = friction.normalize() * mFriction * mMass * Time::DeltaTime();

			// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� ū ���.
			if (mVelocity.length() <= friction.length())
			{
				// ����.
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