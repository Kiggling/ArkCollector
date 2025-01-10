#include "acBossScriptComponent.h"
#include "acTransformComponent.h"
#include "acAnimatorComponent.h"
#include "acGameObject.h"
#include "acInput.h"
#include "acTime.h"
#include "acPlayer.h"
#include "acColliderComponent.h"
#include "acObject.h"
#include "acBoxCollidier2DComponent.h"
#include "acResources.h"

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
		, mStatComponent(nullptr)
		, mAnimatorComponent(nullptr)
		, mTransformComponent(nullptr)
		, mColliderComponent(nullptr)
		, mbAttack(false)
		, mAttackDirection(eDirection::Down)
		, mTargetPlayer(nullptr)
		, mEffects{}
		, mEffectSizes{ {48.f, 48.f}, {32.f, 32.f}, {64.f, 64.f} }
	{
	}
	BossScriptComponent::~BossScriptComponent()
	{
	}
	void BossScriptComponent::Initialize()
	{
		mStatComponent = GetOwner()->GetComponent<BossStatComponent>();
		mAnimatorComponent = GetOwner()->GetComponent<AnimatorComponent>();
		mTransformComponent = GetOwner()->GetComponent<TransformComponent>();
		mColliderComponent = GetOwner()->GetComponent<ColliderComponent>();
		for (int i=0; i<4; i++)
		{
			mEffects[i] = object::Instantiate<Projectile>(enums::ELayerType::BossParticle, GetOwner()->GetComponent<TransformComponent>()->GetPosition());
			mEffects[i]->SetStartPosition(GetOwner()->GetComponent<TransformComponent>()->GetPosition());
			
			// ProjectileScriptComponent* projScript = mEffects[i]->AddComponent<ProjectileScriptComponent>();
			
			BoxCollidier2DComponent* projBoxCol = mEffects[i]->AddComponent<BoxCollidier2DComponent>();
			projBoxCol->SetActivate(false);

			AnimatorComponent* projAnimator = mEffects[i]->AddComponent<AnimatorComponent>();
			graphics::Texture* projTexture = Resources::Find<graphics::Texture>(L"Dust");
			projAnimator->CreateAnimation(L"Dust", projTexture, math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 6, 0.2f);

			projTexture = Resources::Find<graphics::Texture>(L"WaveSmallDown");
			projAnimator->CreateAnimation(L"WaveSmallDown", projTexture, math::Vector2(0.0f, 0.0f), math::Vector2(32.0f, 32.0f), math::Vector2::Zero, 3, 0.2f);
			projTexture = Resources::Find<graphics::Texture>(L"WaveSmallUp");
			projAnimator->CreateAnimation(L"WaveSmallUp", projTexture, math::Vector2(0.0f, 0.0f), math::Vector2(32.0f, 32.0f), math::Vector2::Zero, 3, 0.2f);
			projTexture = Resources::Find<graphics::Texture>(L"WaveSmallRight");
			projAnimator->CreateAnimation(L"WaveSmallRight", projTexture, math::Vector2(0.0f, 0.0f), math::Vector2(32.0f, 32.0f), math::Vector2::Zero, 3, 0.2f);
			projTexture = Resources::Find<graphics::Texture>(L"WaveSmallLeft");
			projAnimator->CreateAnimation(L"WaveSmallLeft", projTexture, math::Vector2(0.0f, 0.0f), math::Vector2(32.0f, 32.0f), math::Vector2::Zero, 3, 0.2f);

			projTexture = Resources::Find<graphics::Texture>(L"WaveBigDown");
			projAnimator->CreateAnimation(L"WaveBigDown", projTexture, math::Vector2(0.0f, 0.0f), math::Vector2(64.0f, 64.0f), math::Vector2::Zero, 3, 0.2f);
			projTexture = Resources::Find<graphics::Texture>(L"WaveBigUp");
			projAnimator->CreateAnimation(L"WaveBigUp", projTexture, math::Vector2(0.0f, 0.0f), math::Vector2(64.0f, 64.0f), math::Vector2::Zero, 3, 0.2f);
			projTexture = Resources::Find<graphics::Texture>(L"WaveBigRight");
			projAnimator->CreateAnimation(L"WaveBigRight", projTexture, math::Vector2(0.0f, 0.0f), math::Vector2(64.0f, 64.0f), math::Vector2::Zero, 3, 0.2f);
			projTexture = Resources::Find<graphics::Texture>(L"WaveBigLeft");
			projAnimator->CreateAnimation(L"WaveBigLeft", projTexture, math::Vector2(0.0f, 0.0f), math::Vector2(64.0f, 64.0f), math::Vector2::Zero, 3, 0.2f);
			
			//projTexture = Resources::Find<graphics::Texture>(L"RainSmallOrange");
			//projAnimator->CreateAnimation(L"RainSmallOrange", projTexture, math::Vector2(0.0f, 0.0f), math::Vector2(64.0f, 64.0f), math::Vector2::Zero, 3, 0.2f);
			//projTexture = Resources::Find<graphics::Texture>(L"RainSmallYello");
			//projAnimator->CreateAnimation(L"RainSmallYello", projTexture, math::Vector2(0.0f, 0.0f), math::Vector2(64.0f, 64.0f), math::Vector2::Zero, 3, 0.2f);
			//projTexture = Resources::Find<graphics::Texture>(L"RainSmallRed");
			//projAnimator->CreateAnimation(L"RainSmallRed", projTexture, math::Vector2(0.0f, 0.0f), math::Vector2(64.0f, 64.0f), math::Vector2::Zero, 3, 0.2f);
			//projTexture = Resources::Find<graphics::Texture>(L"RainSmallBlue");
			//projAnimator->CreateAnimation(L"RainSmallBlue", projTexture, math::Vector2(0.0f, 0.0f), math::Vector2(64.0f, 64.0f), math::Vector2::Zero, 3, 0.2f);
			//projTexture = Resources::Find<graphics::Texture>(L"RainSmallGreen");
			//projAnimator->CreateAnimation(L"RainSmallGreen", projTexture, math::Vector2(0.0f, 0.0f), math::Vector2(64.0f, 64.0f), math::Vector2::Zero, 3, 0.2f);

			//projTexture = Resources::Find<graphics::Texture>(L"RainBigOrange");
			//projAnimator->CreateAnimation(L"RainBigOrange", projTexture, math::Vector2(0.0f, 0.0f), math::Vector2(6.0f, 23.0f), math::Vector2::Zero, 3, 0.2f);
			//projTexture = Resources::Find<graphics::Texture>(L"RainBigYello");
			//projAnimator->CreateAnimation(L"RainBigYello", projTexture, math::Vector2(0.0f, 0.0f), math::Vector2(64.0f, 64.0f), math::Vector2::Zero, 3, 0.2f);
			//projTexture = Resources::Find<graphics::Texture>(L"RainBigRed");
			//projAnimator->CreateAnimation(L"RainBigRed", projTexture, math::Vector2(0.0f, 0.0f), math::Vector2(64.0f, 64.0f), math::Vector2::Zero, 3, 0.2f);
			//projTexture = Resources::Find<graphics::Texture>(L"RainBigBlue");
			//projAnimator->CreateAnimation(L"RainBigBlue", projTexture, math::Vector2(0.0f, 0.0f), math::Vector2(64.0f, 64.0f), math::Vector2::Zero, 3, 0.2f);
			//projTexture = Resources::Find<graphics::Texture>(L"RainBigGray");
			//projAnimator->CreateAnimation(L"RainBigGray", projTexture, math::Vector2(0.0f, 0.0f), math::Vector2(64.0f, 64.0f), math::Vector2::Zero, 3, 0.2f);

		}
	}
	void BossScriptComponent::Update()
	{
		setDirection();

		if (mEffects[0]->GetRange() != 500.f)
		{
			int a = 0;
		}
		if (!mbAttack && mAttackCool < 6.f)
		{
			mAttackCool += Time::DeltaTime();
		}

		switch (mState)
		{
		case ac::BossScriptComponent::eState::None:
		{
			none();
		}
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
		float hp = mStatComponent->GetHp();

		hp = (hp - 25.f >= 0 ? hp - 25.f : 0);
		mStatComponent->SetHp(hp);

		if (hp == 0)
		{
			playAnimation(L"Death", false);
			mState = eState::Death;
		}
		else
		{
			playAnimation(L"Hurt", false);
			mState = eState::Hurt;
		}
	}
	void BossScriptComponent::OnCollisionStay(ColliderComponent* other)
	{
	}
	void BossScriptComponent::OnCollisionExit(ColliderComponent* other)
	{
	}
	void BossScriptComponent::none()
	{
		mTime += Time::DeltaTime();

		if (mTime > 1.f)
		{
			mTime = 0.f;
			mState = eState::Land;
			playAnimation(L"Land", false);
			playEffectAnimation(0, L"Dust", false, { 0.f, 20.f }, { 2.f, 2.f }, false);
		}
	}
	void BossScriptComponent::idle()
	{
		resetEffect();

		if (isAttacking())
		{
			mTime = 0.f;
			return;
		}
		if (hasToTeleport())
		{
			mTime = 0.f;
			return;
		}

		mTime += Time::DeltaTime();

		if (mTime > 1.5f)
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
			mTime = 0.f;
			return;
		}
		if (hasToTeleport())
		{
			mTime = 0.f;
			return;
		}

		mTime += Time::DeltaTime();

		if (mTime > 3.f)
		{
			mState = eState::Idle;
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
			mTransformComponent->SetPosition(mTargetPosition);
			mAnimatorComponent->StopAnimation();
			mColliderComponent->SetActivate(false);

			mState = eState::None;
		}
	}
	void BossScriptComponent::land()
	{
		mColliderComponent->SetActivate(true);

		if (mAnimatorComponent->IsComplete())
		{
			mAttackCool = 2.5f;
			mState = eState::Idle;
			playAnimation(L"Idle", false);
		}
	}
	void BossScriptComponent::attack()
	{
		if (mAnimatorComponent->IsComplete())
		{
			if (mAttackType == eAttack::Attack01)
			{
				math::Vector2 offset = { 0.f, 0.f };

				switch (mAnimationDirection)
				{
				case ac::BossScriptComponent::eDirection::Down:
					offset = { 0.f, 30.f };
					break;
				case ac::BossScriptComponent::eDirection::Up:
					offset = { 0.f, -30.f };
					break;
				case ac::BossScriptComponent::eDirection::Left:
					offset = { -30.f, 0.f };
					break;
				case ac::BossScriptComponent::eDirection::Right:
					offset = { 30.f, 0.f };
					break;
				case ac::BossScriptComponent::eDirection::End:
					break;
				default:
					break;
				}
				
				math::Vector2 scale(2.f, 2.f);
				setEffectCollision(0, eEffect::WaveSmall, scale);
				playEffectAnimation(0, L"WaveSmall", true, offset, scale, false);
			}

			mAttackCool = 0.f;
			mbAttack = false;
			mState = eState::Idle;
			mAttackType = eAttack::None;
			playAnimation(L"Idle", true);
		}
	}
	void BossScriptComponent::hurt()
	{
		if (mAnimatorComponent->IsComplete())
		{
			mState = eState::Idle;
			playAnimation(L"Idle", true);
		}
	}
	void BossScriptComponent::death()
	{
		mColliderComponent->SetActivate(false);
	}
	void BossScriptComponent::playAnimation(std::wstring name, bool loop)
	{
		mAnimatorComponent->PlayAnimation(name + directions[(int)mAnimationDirection], loop);
	}
	void BossScriptComponent::playEffectAnimation(UINT idx, std::wstring name, bool hasDirection, math::Vector2 offset, math::Vector2 scale, bool loop)
	{
		TransformComponent* tr = mEffects[idx]->GetComponent<TransformComponent>();
		math::Vector2 pos = mTransformComponent->GetPosition() + offset;
		tr->SetPosition(pos);
		tr->SetScale(scale);

		if (hasDirection)
		{
			mEffects[idx]->GetComponent<AnimatorComponent>()->PlayAnimation(name + directions[(int)mAnimationDirection], loop);
		}
		else
		{
			mEffects[idx]->GetComponent<AnimatorComponent>()->PlayAnimation(name, loop);
		}
	}
	void BossScriptComponent::setEffectCollision(UINT idx, eEffect effectType, math::Vector2 scale)
	{
		ColliderComponent* col = mEffects[idx]->GetComponent<ColliderComponent>();
		col->SetActivate(true);
		col->SetSize(mEffectSizes[(UINT)effectType] * scale);
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
	void BossScriptComponent::resetEffect()
	{
		for (int i = 0; i < 4; i++)
		{
			AnimatorComponent* animator = mEffects[i]->GetComponent<AnimatorComponent>();
			ColliderComponent* col = mEffects[i]->GetComponent<ColliderComponent>();

			if (animator == nullptr || col == nullptr) continue;

			if (mEffects[i]->GetComponent<AnimatorComponent>()->IsComplete())
			{
				mEffects[i]->GetComponent<AnimatorComponent>()->StopAnimation();
				mEffects[i]->GetComponent<ColliderComponent>()->SetActivate(false);
			}
		}
	}
	bool BossScriptComponent::isAttacking()
	{
		if (mDistanceFromTarget.length() <= 100.f && mAttackCool >= 3.f)
		{
			mbAttack = true;
			mState = eState::Attack;

			//int attackState = rand() % 3;

			int attackState = 0;
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
	bool BossScriptComponent::hasToTeleport()
	{
		if (mAttackCool >= 6.f)
		{
			mState = eState::Jump;
			playAnimation(L"Jump", false);

			mAttackCool = 0.f;
			return true;
		}
		return false;
	}
}
