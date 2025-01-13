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
#include "acProjectileScriptComponent.h"
#include "acApplication.h"
#include "acWall.h"
#include "acWallScriptComponent.h"
#include "acWallStatComponent.h"

extern ac::Application application;

namespace ac
{
	BossScriptComponent::FAnimationInfo animationInfo[4] = {
		{ L"Dust", math::Vector2(2.f, 2.f), math::Vector2(48.f, 48.f), 6, 0.2f},
		{ L"WaveSmall", math::Vector2(2.f, 2.f), math::Vector2(32.f, 32.f), 3, 0.2f},
		{ L"WaveBig", math::Vector2(1.5f, 1.5f), math::Vector2(64.f, 64.f), 1, 0.2f},
		{ L"RainBigRed", math::Vector2(1.5f, 1.5f), math::Vector2(6.f,26.f), 8, 0.2f},
	};
	BossScriptComponent::FProjectileInfo projectileInfo[4] = {
		{ ProjectileScriptComponent::eEffectType::Effect, ProjectileScriptComponent::eDamageType::None, 0.f, math::Vector2::Zero, 0.f },
		{ ProjectileScriptComponent::eEffectType::Effect, ProjectileScriptComponent::eDamageType::Effect, 50.f, math::Vector2::Zero, 0.f },
		{ ProjectileScriptComponent::eEffectType::Projectile, ProjectileScriptComponent::eDamageType::Effect, 1.f, math::Vector2::Zero, 250.f },
		{ ProjectileScriptComponent::eEffectType::Projectile, ProjectileScriptComponent::eDamageType::Projectile, 1.f, math::Vector2(0.f, 100.f), 120.f },
	};
	math::Vector2 colliderInfo[4]
	{
		math::Vector2::One,
		math::Vector2(32.f, 32.f),
		math::Vector2(64.f, 22.f),
		math::Vector2(6.f,26.f),
	};
	math::Vector2 waveOffset[4] = {
		{ 0.f, 30.f },
		{ 0.f, -30.f },
		{ -30.f, 0.f },
		{ 30.f, 0.f },
	};
	math::Vector2 waveBigVelocity[4] = {
		{ 0.f, 500.f },
		{ 0.f, -500.f },
		{ -500.f, 0.f },
		{ 500.f, 0.f },
	};

	BossScriptComponent::BossScriptComponent()
		: mTime(0.0f)
		, mAttackCool(0.0f)
		, mTargetPosition(math::Vector2::Zero)
		, mDistanceFromTarget(math::Vector2::Zero)
		, mMoveDirection(math::Vector2::Zero)
		, mState(eState::Idle)
		, mAnimationDirection(eDirection::Down)
		, mAttackType(eAttack::None)
		, mGimmick(eGimmick::None)
		, mGimmickState(eGimmickState::None)
		, mStatComponent(nullptr)
		, mAnimatorComponent(nullptr)
		, mTransformComponent(nullptr)
		, mColliderComponent(nullptr)
		, mbAttack(false)
		, mTargetPlayer(nullptr)
		, mGimmickCheck{}
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
	}
	void BossScriptComponent::Update()
	{
		setDirection();
		checkGimmick();
		
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
		case ac::BossScriptComponent::eState::Gimmick:
		{
			gimmick();
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
			playEffectAnimation(animationInfo[(UINT)eEffect::Dust], projectileInfo[(UINT)eEffect::Dust], colliderInfo[(UINT)eEffect::Dust], (UINT)eDirection::None, math::Vector2(0.f, 20.f), false);
		}
	}
	void BossScriptComponent::idle()
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
			mState = eState::Walk;
			playAnimation(L"Walk", false);
		}
	}
	void BossScriptComponent::attack()
	{
		switch (mAttackType)
		{
		case ac::BossScriptComponent::eAttack::None:
			break;
		case ac::BossScriptComponent::eAttack::Attack01:
			if (mAnimatorComponent->IsComplete())
			{
				playEffectAnimation(animationInfo[(UINT)eEffect::WaveSmall], projectileInfo[(UINT)eEffect::WaveSmall], colliderInfo[(UINT)eEffect::WaveSmall], (UINT)mAnimationDirection, waveOffset[(UINT)mAnimationDirection], true);
			}
			break;
		case ac::BossScriptComponent::eAttack::Attack02:
			for (int direction = 0; direction < (UINT)eDirection::None; direction++)
			{
				if (mTime <= 0.1f)
				{
					math::Vector2 colInfo = colliderInfo[(UINT)eEffect::WaveBig];
					if (direction == (UINT)eDirection::Left || direction == (UINT)eDirection::Right)
					{
						colInfo.swapXY();
					}
					projectileInfo[(UINT)eEffect::WaveBig].velocity = waveBigVelocity[direction];
					playEffectAnimation(animationInfo[(UINT)eEffect::WaveBig], projectileInfo[(UINT)eEffect::WaveBig], colInfo, direction, waveOffset[(UINT)direction], true);
				}
			}
			if (mTime >= 0.4f) mTime = 0.f;
			mTime += Time::DeltaTime();
			break;
		case ac::BossScriptComponent::eAttack::Attack03:
			if (mTime <= 0.04f)
			{
				UINT range = 300;
				math::Vector2 offset = math::Vector2(rand() % (range / 2), rand() % (range / 2));
				offset = offset * math::Vector2((rand() % 2 ? 1 : -1), (rand() % 2 ? 1 : -1));
				offset.y -= 50.f;

				playEffectAnimation(animationInfo[(UINT)eEffect::RainBigRed], projectileInfo[(UINT)eEffect::RainBigRed], colliderInfo[(UINT)eEffect::RainBigRed], (UINT)eDirection::None, offset, true);
			}
			if (mTime >= 0.2) mTime = 0.f;
			mTime += Time::DeltaTime();
			break;
		case ac::BossScriptComponent::eAttack::End:
			break;
		default:
			break;
		}
		if (mAnimatorComponent->IsComplete())
		{
			mTime = 0.f;
			mAttackCool = 0.f;
			mbAttack = false;
			mState = eState::Idle;
			mAttackType = eAttack::None;
			playAnimation(L"Idle", true);
		}
	}
	void BossScriptComponent::gimmick()
	{
		switch (mGimmick)
		{
		case ac::BossScriptComponent::eGimmick::None:
			break;
		case ac::BossScriptComponent::eGimmick::HP100:
			gimmickHP100();
			break;
		case ac::BossScriptComponent::eGimmick::HP0:
			gimmickHP0();
			break;
		case ac::BossScriptComponent::eGimmick::End:
			break;
		default:
			break;
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
	void BossScriptComponent::playEffectAnimation(FAnimationInfo aniInfo, FProjectileInfo projInfo, math::Vector2 colInfo, int direction, math::Vector2 offset, bool collisionActivate, bool loop)
	{
		Projectile* proj = object::Instantiate<Projectile>(enums::ELayerType::BossParticle);
		
		TransformComponent* tr = proj->GetComponent<TransformComponent>();
		math::Vector2 pos = mTransformComponent->GetPosition() + offset;
		tr->SetPosition(pos);
		tr->SetScale(aniInfo.scale);
		proj->SetStartPosition(pos);
		proj->SetVelocity(projInfo.velocity);
		proj->SetRange(projInfo.range);

		ProjectileScriptComponent* projScript = proj->AddComponent<ProjectileScriptComponent>();
		projScript->SetDamage(projInfo.damage);
		projScript->SetEffectType(projInfo.effectType);
		projScript->SetDamageType(projInfo.damageType);

		if (collisionActivate)
		{
			BoxCollidier2DComponent* projBoxCol = proj->AddComponent<BoxCollidier2DComponent>();
			projBoxCol->SetSize(colInfo * aniInfo.scale);
		}

		AnimatorComponent* projAnimator = proj->AddComponent<AnimatorComponent>();
		std::wstring animationName = aniInfo.name;
		if (direction != (UINT)eDirection::None)
		{
			animationName += directions[direction];
		}
		graphics::Texture* projTexture = Resources::Find<graphics::Texture>(animationName);
		projAnimator->CreateAnimation(animationName, projTexture, math::Vector2(0.0f, 0.0f), aniInfo.size, math::Vector2::Zero, aniInfo.spriteLength, aniInfo.duration);
		proj->GetComponent<AnimatorComponent>()->PlayAnimation(animationName, loop);

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
	void BossScriptComponent::checkGimmick()
	{
		if (mState == eState::Death || mState == eState::Gimmick || mState == eState::Hurt)
		{
			return;
		}
		if (mStatComponent->GetHp() <= 100.f && mGimmickCheck[2] == false)
		{
			mState = eState::Gimmick;
			mGimmick = eGimmick::HP100;
			mGimmickState = eGimmickState::Jump;
			playAnimation(L"Jump", false);
			mTime = 0.f;
			mAttackCool = 0.f;
			mColliderComponent->SetActivate(false);
		}
		if (mStatComponent->GetHp() == 0.f && mGimmickCheck[3] == false)
		{
			mState = eState::Gimmick;
			mGimmick = eGimmick::HP0;
			mGimmickState = eGimmickState::Jump;
			playAnimation(L"Jump", false);
			mTime = 0.f;
			mAttackCool = 0.f;
			mColliderComponent->SetActivate(false);
		}
	}
	void BossScriptComponent::gimmickHP100()
	{
		switch (mGimmickState)
		{
		case ac::BossScriptComponent::eGimmickState::None:
			noneHP100();
			break;
		case ac::BossScriptComponent::eGimmickState::Jump:
			jumpHP100();
			break;
		case ac::BossScriptComponent::eGimmickState::Land:
			landHP100();
			break;
		case ac::BossScriptComponent::eGimmickState::Wait:
			waitHP100();
			break;
		case ac::BossScriptComponent::eGimmickState::Attack:
			attackHP100();
			break;
		case ac::BossScriptComponent::eGimmickState::End:
			break;
		default:
			break;
		}

		// 플레이어를 주시
		// 맵 좌우에 벽이 하나씩 생김
		// 벽 뒤에 숨으면 생존
	}
	void BossScriptComponent::gimmickHP0()
	{
		int a = 0;
	}
	void BossScriptComponent::createWall()
	{
		Wall* wall = object::Instantiate<Wall>(enums::ELayerType::Object);

		TransformComponent* tr = wall->AddComponent<TransformComponent>();
		math::Vector2 wallPos = mTransformComponent->GetPosition();
		math::Vector2 offset = math::Vector2(application.GetWidth() / 5.f, application.GetHeight() / 5.f);
		math::Vector2 collisionOffset = math::Vector2(0.f, 28.f);
		int direction = rand() % 4;

		wall->SetDirection((Wall::eDirection)direction);
		if (direction == (UINT)eDirection::Down)
		{
			wallPos.y += offset.y;
			collisionOffset.y += 15.f;
		}
		else if (direction == (UINT)eDirection::Up)
		{
			wallPos.y -= offset.y;
			collisionOffset.y -= 15.f;
		}
		else if (direction == (UINT)eDirection::Left)
		{
			wallPos.x -= offset.x;
			collisionOffset.x -= 15.f;
		}
		else if (direction == (UINT)eDirection::Right)
		{
			wallPos.x += offset.x;
			collisionOffset.x += 15.f;
		}

		tr->SetPosition(wallPos);
		tr->SetScale(math::Vector2(2.f, 2.f));

		BoxCollidier2DComponent* boxWall = wall->AddComponent<BoxCollidier2DComponent>();
		boxWall->SetSize(math::Vector2(36.f, 36.f) * tr->GetScale());
		boxWall->SetOffset(collisionOffset);

		WallStatComponent* statWall = wall->AddComponent<WallStatComponent>();
		WallScriptComponent* scriptWall = wall->AddComponent<WallScriptComponent>();

		AnimatorComponent* wallAnimator = wall->AddComponent<AnimatorComponent>();
		std::wstring animationName = L"WallBuild";
		animationName += directions[direction];
		graphics::Texture* wallTexture = Resources::Find<graphics::Texture>(animationName);
		wallAnimator->CreateAnimation(animationName, wallTexture, math::Vector2(0.0f, 0.0f), math::Vector2(36.0f, 64.0f), math::Vector2::Zero, 6, 0.2f);
		wallAnimator->PlayAnimation(animationName, false);
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
	void BossScriptComponent::noneHP100()
	{
		mTime += Time::DeltaTime();

		if (mTime > 1.f)
		{
			mTime = 0.f;
			mGimmickState = eGimmickState::Land;
			playAnimation(L"Land", false);
			playEffectAnimation(animationInfo[(UINT)eEffect::Dust], projectileInfo[(UINT)eEffect::Dust], colliderInfo[(UINT)eEffect::Dust], (UINT)eDirection::None, math::Vector2(0.f, 20.f), false);
		}
	}
	void BossScriptComponent::jumpHP100()
	{
		if (mAnimatorComponent->IsComplete())
		{
			math::Vector2 pos = math::Vector2::Zero;
			pos.x = application.GetWidth() / 2.f;
			pos.y = application.GetHeight() / 2.f;

			mAnimatorComponent->StopAnimation();
			mTransformComponent->SetPosition(pos);

			mGimmickState = eGimmickState::None;
		}
	}
	void BossScriptComponent::landHP100()
	{
		if (mAnimatorComponent->IsComplete())
		{
			mGimmickState = eGimmickState::Wait;
			playAnimation(L"Attack01HalfLeft", false);
			createWall();
		}
	}
	void BossScriptComponent::waitHP100()
	{
		mTime += Time::DeltaTime();

		math::Vector2 pos = mTransformComponent->GetPosition();

		if (mAnimatorComponent->IsComplete())
		{
			playAnimation(L"Attack01SwordUp", false);
		}

		if (mTime >= 3.f)
		{
			if ((int)(mTime * 10) % 2)
			{
				pos.x += 0.5f;
			}
			else
			{
				pos.x -= 0.5f;
			}
			mTransformComponent->SetPosition(pos);
		}
		if (mTime >= 6.f)
		{
			mTime = 0.f;
			mGimmickState = eGimmickState::Attack;
			playAnimation(L"Attack01HalfRight", false);

			FAnimationInfo aniInfo = {
				L"WaveBig", 
				math::Vector2(10.f, 10.f),
				math::Vector2(64.f, 64.f), 
				1, 
				0.2f
			};
			FProjectileInfo projInfo = {
				ProjectileScriptComponent::eEffectType::Projectile,
				ProjectileScriptComponent::eDamageType::Projectile,
				100.f,
				waveBigVelocity[(UINT)mAnimationDirection],
				800.f
			};
			math::Vector2 colInfo = colliderInfo[(UINT)eEffect::WaveBig];
			if (mAnimationDirection == eDirection::Left || mAnimationDirection == eDirection::Right)
			{
				colInfo.swapXY();
			}
			playEffectAnimation(aniInfo, projInfo, colInfo, (UINT)mAnimationDirection, waveOffset[(UINT)mAnimationDirection], true);
		}
	}
	void BossScriptComponent::attackHP100()
	{
		mTime += Time::DeltaTime();

		if (mTime > 2.f)
		{
			mTime = 0.f;
			mState = eState::Idle;
			mGimmick = eGimmick::None;
			mGimmickState = eGimmickState::End;
			mColliderComponent->SetActivate(true);
			mGimmickCheck[2] = true;
		}
	}
}
