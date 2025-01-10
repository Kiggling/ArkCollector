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
		class Player* mTargetPlayer;					// ������ Ÿ��
		float mTime;									// idle, walk ���� �ൿ���� �Ѿ�� ��� �ð�
		float mAttackCool;								// ������ ���� ��Ÿ��(3�ʸ��� �� ���� ����, 6���̻� ������ ���� �ʾҴٸ� Ÿ�� ��ġ�� �����̵�(���� �� ����))
		math::Vector2 mTargetPosition;					// Ÿ���� ��ġ
		math::Vector2 mDistanceFromTarget;				// Ÿ�ٰ��� �Ÿ�
		math::Vector2 mMoveDirection;					// ������ ���� �̵��� ����
		math::Vector2 mEffectSizes[3];					// ������ ����Ʈ ũ��
		eState mState;									// ���� ����
		eAttack mAttackType;							// ���� �Ϲ� ���� Ÿ�� (3���� ����)
		eDirection mAnimationDirection;					// ����� ���ϸ��̼� ����
		BossStatComponent* mStatComponent;				// ���� ���� ������Ʈ
		class AnimatorComponent* mAnimatorComponent;	// ���� �ִϸ��̼� ������Ʈ
		class TransformComponent* mTransformComponent;	// ���� ��ġ ���� ������Ʈ
		class ColliderComponent* mColliderComponent;	// ���� �浹 ������Ʈ
		bool mbAttack;									// ������ �����ϰ� �ִ���
		eDirection mAttackDirection;					// ������ ���ݹ���
		Projectile* mEffects[4];						// ���� ����Ʈ (�� ���� �ϳ��� ����Ʈ�� ����� ��� (index 0)�� ���, �� ���� ���� ����Ʈ(ex �߻�ü)�� ���ȴٸ� �ٸ� index�� ���)

	};
}

