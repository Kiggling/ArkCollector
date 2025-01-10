#pragma once
#include "..\\ArkCollectorEngine_SOURCE\acScriptComponent.h"
#include "acBossStatComponent.h"
#include "acProjectile.h"
#include "acProjectileScriptComponent.h"

namespace ac
{
	class BossScriptComponent : public ScriptComponent
	{
	public:
		enum class eState
		{
			None,
			Idle,
			Walk,
			Jump,
			Land,
			Attack,
			Hurt,
			Death,
			End,
		};
		enum class eAttack
		{
			None,
			Attack01,
			Attack02,
			Attack03,
			End,
		};

		enum class eDirection
		{
			Down,
			Up,
			Left,
			Right,
			End,
		};

		enum class eEffect
		{
			Dust,
			WaveSmall,
			WaveBig,
			End,
		};

		BossScriptComponent();
		~BossScriptComponent();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

		virtual void OnCollisionEnter(class ColliderComponent* other) override;
		virtual void OnCollisionStay(class ColliderComponent* other) override;
		virtual void OnCollisionExit(class ColliderComponent* other) override;

		void SetTarget(class Player* InTarget) { mTargetPlayer = InTarget; }

	private:
		eAttack attackTypes[3] = { eAttack::Attack01, eAttack::Attack02 , eAttack::Attack03 };
		std::wstring directions[4] = { L"Down", L"Up", L"Left", L"Right" };

		void none();
		void idle();
		void walk();
		void jump();
		void land();
		void attack();
		void hurt();
		void death();
		void playAnimation(std::wstring name, bool loop);
		void playEffectAnimation(UINT idx, std::wstring name, bool hasDirection, math::Vector2 offset, math::Vector2 scale, bool loop);
		void setEffectCollision(UINT idx, eEffect effectType, math::Vector2 scale);
		void setDirection();
		void resetEffect();
		bool isAttacking();
		bool hasToTeleport();
	private:
		class Player* mTargetPlayer;					// 보스의 타겟
		float mTime;									// idle, walk 등의 행동으로 넘어가는 대기 시간
		float mAttackCool;								// 보스의 공격 쿨타임(3초마다 한 번씩 공격, 6초이상 공격을 하지 않았다면 타겟 위치로 순간이동(점프 후 랜드))
		math::Vector2 mTargetPosition;					// 타겟의 위치
		math::Vector2 mDistanceFromTarget;				// 타겟과의 거리
		math::Vector2 mMoveDirection;					// 보스가 실제 이동할 방향
		math::Vector2 mEffectSizes[3];					// 보스의 이펙트 크기
		eState mState;									// 보스 상태
		eAttack mAttackType;							// 보스 일반 공격 타입 (3가지 존재)
		eDirection mAnimationDirection;					// 재생할 에니매이션 방향
		BossStatComponent* mStatComponent;				// 보스 스텟 컴포넌트
		class AnimatorComponent* mAnimatorComponent;	// 보스 애니메이션 컴포넌트
		class TransformComponent* mTransformComponent;	// 보스 위치 상태 컴포넌트
		class ColliderComponent* mColliderComponent;	// 보스 충돌 컴포넌트
		bool mbAttack;									// 보스가 공격하고 있는지
		eDirection mAttackDirection;					// 보스의 공격방향
		Projectile* mEffects[4];						// 보스 이펙트 (한 번에 하나의 이펙트만 사용할 경우 (index 0)만 사용, 한 번에 여러 이펙트(ex 발사체)가 사용된다면 다른 index도 사용)

	};
}

