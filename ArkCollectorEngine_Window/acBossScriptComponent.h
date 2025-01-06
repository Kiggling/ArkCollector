#pragma once
#include "..\\ArkCollectorEngine_SOURCE\acScriptComponent.h"

namespace ac
{
	class BossScriptComponent : public ScriptComponent
	{
	public:
		enum class eState
		{
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

		void idle();
		void walk();
		void jump();
		void land();
		void attack();
		void hurt();
		void death();
		void playAnimation(std::wstring name, bool loop);
		void setDirection();
		bool isAttacking();
		bool judgeTeleport();
	private:
		class Player* mTargetPlayer;				// 보스의 타겟
		float mTime;
		float mAttackCool;							// 보스의 공격 쿨타임(3초마다 한 번씩 공격, 6초이상 공격을 하지 않았다면 타겟 위치로 순간이동(점프 후 랜드))
		math::Vector2 mTargetPosition;				// 타겟의 위치
		math::Vector2 mDistanceFromTarget;			// 타겟과의 거리
		math::Vector2 mMoveDirection;				// 보스가 실제 이동할 방향
		eState mState;
		eAttack mAttackType;
		eDirection mAnimationDirection;				// 재생할 에니매이션 방향
		class AnimatorComponent* mAnimatorComponent;
		class TransformComponent* mTransformComponent;
		bool mbAttack;
		eDirection mAttackDirection;

	};
}

