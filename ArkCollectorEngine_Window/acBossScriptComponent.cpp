#include "acBossScriptComponent.h"
#include "acTransformComponent.h"
#include "acAnimatorComponent.h"
#include "acGameObject.h"
#include "acInput.h"
#include "acTime.h"
#include "acPlayer.h"

namespace ac
{

	BossScriptComponent::BossScriptComponent()
		: mTime(0.0f)
		, mAttackCool(0.0f)
		, mTargetPosition(math::Vector2::Zero)
		, mDistanceFromTarget(math::Vector2::Zero)
		, mMoveDirection(math::Vector2::Zero)
		, mState(eState::Idle)
		, mAnimationDirection(eDirection::Down)
		, mAttackType(eAttack::None)
		, mAnimatorComponent(nullptr)
		, mTransformComponent(nullptr)
		, mbAttack(false)
		, mAttackDirection(eDirection::Down)
		, mTargetPlayer(nullptr)
	{
	}
	BossScriptComponent::~BossScriptComponent()
	{
	}
	void BossScriptComponent::Initialize()
	{
		mAnimatorComponent = GetOwner()->GetComponent<AnimatorComponent>();
		mTransformComponent = GetOwner()->GetComponent<TransformComponent>();
	}
	void BossScriptComponent::Update()
	{
		setDirection();

		if (!mbAttack && mAttackCool < 6.f)
		{
			mAttackCool += Time::DeltaTime();
		}

		switch (mState)
		{
		case ac::BossScriptComponent::eState::Idle:
		{
			idle();
		}
			break;
		case ac::BossScriptComponent::eState::Walk:
		{
			walk();
		}
			break;
		case ac::BossScriptComponent::eState::Jump:
		{
			jump();
		}
			break;
		case ac::BossScriptComponent::eState::Land:
		{
			land();
		}
			break;
		case ac::BossScriptComponent::eState::Attack:
		{
			attack();
		}
			break;
		case ac::BossScriptComponent::eState::Hurt:
		{
			hurt();
		}
			break;
		case ac::BossScriptComponent::eState::Death:
		{
			death();
		}
			break;
		case ac::BossScriptComponent::eState::End:
		{

		}
			break;
		default:
			break;
		}
	}
	void BossScriptComponent::LateUpdate()
	{
	}
	void BossScriptComponent::Render(HDC InHdc)
	{
	}
	void BossScriptComponent::OnCollisionEnter(ColliderComponent* other)
	{
	}
	void BossScriptComponent::OnCollisionStay(ColliderComponent* other)
	{
	}
	void BossScriptComponent::OnCollisionExit(ColliderComponent* other)
	{
	}
	void BossScriptComponent::idle()
	{
		if (isAttacking())
		{
			return;
		}
		if (judgeTeleport())
		{
			return;
		}

		mTime += Time::DeltaTime();

		if (mTime > 2.f)
		{
			mState = eState::Walk;
			
			playAnimation(L"Walk", true);

			mTime = 0.0f;
		}
	}
	void BossScriptComponent::walk()
	{
		if (isAttacking())
		{
			return;
		}
		if (judgeTeleport())
		{
			return;
		}

		mTime += Time::DeltaTime();

		if (mTime > 2.f)
		{
			mState = eState::Idle();
			playAnimation(L"Idle", true);

			mTime = 0.0f;
		}

		math::Vector2 pos = mTransformComponent->GetPosition();

		pos.x += mMoveDirection.x * 50.f * Time::DeltaTime();
		pos.y += mMoveDirection.y * 50.f * Time::DeltaTime();

		mTransformComponent->SetPosition(pos);
	}
	void BossScriptComponent::jump()
	{
		if (mAnimatorComponent->IsComplete())
		{
			if (mTime == 0.f)
			{
				mTransformComponent->SetPosition(mTargetPosition);
			}
			if (mTime >= 1.5f)
			{
				mState = eState::Land;
				playAnimation(L"Land", false);
			}
			mTime += Time::DeltaTime();

		}
	}
	void BossScriptComponent::land()
	{
		if (mAnimatorComponent->IsComplete())
		{
			mAttackCool = 1.f;
			mState = eState::Idle;
			playAnimation(L"Idle", false);
		}
	}
	void BossScriptComponent::attack()
	{
		if (mAnimatorComponent->IsComplete())
		{
			mAttackCool = 0.f;
			mbAttack = false;
			mState = eState::Idle();
			mAttackType = eAttack::None;
			playAnimation(L"Idle", true);
		}
	}
	void BossScriptComponent::hurt()
	{
	}
	void BossScriptComponent::death()
	{
	}
	void BossScriptComponent::playAnimation(std::wstring name, bool loop)
	{
		mAnimatorComponent->PlayAnimation(name + directions[(int)mAnimationDirection], loop);
	}
	void BossScriptComponent::setDirection()
	{
		math::Vector2 pos = mTransformComponent->GetPosition();

		TransformComponent* targetTr = mTargetPlayer->GetComponent<TransformComponent>();
		mTargetPosition = targetTr->GetPosition();

		mDistanceFromTarget = mMoveDirection = mTargetPosition - pos;
		mMoveDirection.normalize();

		/* 방향 벡터 부호
		(-,-)	(+,-)
			 기준
		(-,+)	(+,+)
		*/
		if (mMoveDirection.x >= 0 && mMoveDirection.y >= 0)	// 우하단
		{
			if (fabs(mMoveDirection.x) >= fabs(mMoveDirection.y))
			{
				mAnimationDirection = eDirection::Right;
			}
			else
			{
				mAnimationDirection = eDirection::Down;
			}
		}
		else if (mMoveDirection.x >= 0 && mMoveDirection.y < 0) // 우상단
		{
			if (fabs(mMoveDirection.x) >= fabs(mMoveDirection.y))
			{
				mAnimationDirection = eDirection::Right;
			}
			else
			{
				mAnimationDirection = eDirection::Up;
			}
		}
		else if (mMoveDirection.x < 0 && mMoveDirection.y >= 0) // 좌하단
		{
			if (fabs(mMoveDirection.x) >= fabs(mMoveDirection.y))
			{
				mAnimationDirection = eDirection::Left;
			}
			else
			{
				mAnimationDirection = eDirection::Down;
			}
		}
		else if (mMoveDirection.x < 0 && mMoveDirection.y < 0) // 좌상단
		{
			if (fabs(mMoveDirection.x) >= fabs(mMoveDirection.y))
			{
				mAnimationDirection = eDirection::Left;
			}
			else
			{
				mAnimationDirection = eDirection::Up;
			}
		}
	}
	bool BossScriptComponent::isAttacking()
	{
		if (mDistanceFromTarget.length() <= 100.f && mAttackCool >= 3.f)
		{
			mbAttack = true;
			mState = eState::Attack;

			int attackState = rand() % 3;

			mAttackType = attackTypes[attackState];
			switch (mAttackType)
			{
			case ac::BossScriptComponent::eAttack::None:
				break;
			case ac::BossScriptComponent::eAttack::Attack01:
				playAnimation(L"Attack01", false);
				break;
			case ac::BossScriptComponent::eAttack::Attack02:
				playAnimation(L"Attack02", false);
				break;
			case ac::BossScriptComponent::eAttack::Attack03:
				playAnimation(L"Attack03", false);
				break;
			case ac::BossScriptComponent::eAttack::End:
				break;
			default:
				break;
			}

			return true;
		}
		return false;
	}
	bool BossScriptComponent::judgeTeleport()
	{
		if (mAttackCool >= 6.f)
		{
			mState = eState::Jump;
			playAnimation(L"Jump", false);

			return true;
		}
		return false;
	}
}
