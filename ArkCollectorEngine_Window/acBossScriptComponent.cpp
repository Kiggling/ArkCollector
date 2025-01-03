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
		, mDistanceFromTarget(math::Vector2::Zero)
		, mMoveDirection(math::Vector2::Zero)
		, mState(eState::Idle)
		, mAnimationDirection(eDirection::Down)
		, mAnimatorComponent(nullptr)
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
	}
	void BossScriptComponent::Update()
	{
		if (mAnimatorComponent == nullptr)
		{
			mAnimatorComponent = GetOwner()->GetComponent<AnimatorComponent>();
		}

		setDirection();

		if (!mbAttack && mAttackCool < 3.f)
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
		case ac::BossScriptComponent::eState::Attack01:
		{
			attack01();
		}
			break;
		case ac::BossScriptComponent::eState::Attack02:
		{
			attack02();
		}
			break;
		case ac::BossScriptComponent::eState::Attack03:
		{
			attack03();
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
		if (mDistanceFromTarget.length() <= 100.f && mAttackCool >= 3.f)
		{
			mbAttack = true;

			int attackState = rand() % 3;

			mState = attackType[attackState];
			switch (mState)
			{
			case ac::BossScriptComponent::eState::Attack01:
				playAnimation(L"Attack01", false);
				break;
			case ac::BossScriptComponent::eState::Attack02:
				playAnimation(L"Attack02", false);
				break;
			case ac::BossScriptComponent::eState::Attack03:
				playAnimation(L"Attack03", false);
				break;
			default:
				break;
			}

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
		if (mDistanceFromTarget.length() <= 100.f && mAttackCool >= 3.f)
		{
			mbAttack = true;

			int attackState = rand() % 3;

			mState = attackType[attackState];
			switch (mState)
			{
			case ac::BossScriptComponent::eState::Attack01:
				playAnimation(L"Attack01", false);
				break;
			case ac::BossScriptComponent::eState::Attack02:
				playAnimation(L"Attack02", false);
				break;
			case ac::BossScriptComponent::eState::Attack03:
				playAnimation(L"Attack03", false);
				break;
			default:
				break;
			}

			return;
		}

		mTime += Time::DeltaTime();

		if (mTime > 2.f)
		{
			mState = eState::Idle();
			playAnimation(L"Idle", true);
		}

		TransformComponent* tr = GetOwner()->GetComponent<TransformComponent>();
		math::Vector2 pos = tr->GetPosition();

		pos.x += mMoveDirection.x * 50.f * Time::DeltaTime();
		pos.y += mMoveDirection.y * 50.f * Time::DeltaTime();

		tr->SetPosition(pos);
	}
	void BossScriptComponent::jump()
	{
	}
	void BossScriptComponent::land()
	{
	}
	void BossScriptComponent::attack01()
	{
		if (mAnimatorComponent->IsComplete())
		{
			mAttackCool = 0.f;
			mbAttack = false;
			mState = eState::Idle();
			playAnimation(L"Idle", true);
		}
	}
	void BossScriptComponent::attack02()
	{
		if (mAnimatorComponent->IsComplete())
		{
			mAttackCool = 0.f;
			mbAttack = false;
			mState = eState::Idle();
			playAnimation(L"Idle", true);
		}
	}
	void BossScriptComponent::attack03()
	{
		if (mAnimatorComponent->IsComplete())
		{
			mAttackCool = 0.f;
			mbAttack = false;
			mState = eState::Idle();
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
		TransformComponent* tr = GetOwner()->GetComponent<TransformComponent>();
		math::Vector2 pos = tr->GetPosition();

		TransformComponent* targetTr = mTargetPlayer->GetComponent<TransformComponent>();
		math::Vector2 targetPos = targetTr->GetPosition();

		mDistanceFromTarget = mMoveDirection = targetPos - pos;
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
}
