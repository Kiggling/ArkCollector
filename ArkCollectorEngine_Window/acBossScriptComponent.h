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
		class Player* mTargetPlayer;				// ������ Ÿ��
		float mTime;
		float mAttackCool;							// ������ ���� ��Ÿ��(3�ʸ��� �� ���� ����, 6���̻� ������ ���� �ʾҴٸ� Ÿ�� ��ġ�� �����̵�(���� �� ����))
		math::Vector2 mTargetPosition;				// Ÿ���� ��ġ
		math::Vector2 mDistanceFromTarget;			// Ÿ�ٰ��� �Ÿ�
		math::Vector2 mMoveDirection;				// ������ ���� �̵��� ����
		eState mState;
		eAttack mAttackType;
		eDirection mAnimationDirection;				// ����� ���ϸ��̼� ����
		class AnimatorComponent* mAnimatorComponent;
		class TransformComponent* mTransformComponent;
		bool mbAttack;
		eDirection mAttackDirection;

	};
}

