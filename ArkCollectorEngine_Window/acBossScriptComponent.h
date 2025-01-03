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
			Attack01,
			Attack02,
			Attack03,
			Hurt,
			Death,
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
		eState attackType[3] = { eState::Attack01, eState::Attack02 , eState::Attack03 };
		std::wstring directions[4] = { L"Down", L"Up", L"Left", L"Right" };

		void idle();
		void walk();
		void jump();
		void land();
		void attack01();
		void attack02();
		void attack03();
		void hurt();
		void death();
		void playAnimation(std::wstring name, bool loop);
		void setDirection();
		bool isAttacking();
	private:
		class Player* mTargetPlayer;	// ������ Ÿ��
		float mTime;
		float mAttackCool;
		math::Vector2 mDistanceFromTarget; // Ÿ�ٰ��� �Ÿ�
		math::Vector2 mMoveDirection;	// ������ ���� �̵��� ����
		eState mState;
		eDirection mAnimationDirection;	// ����� ���ϸ��̼� ����
		class AnimatorComponent* mAnimatorComponent;
		bool mbAttack;
		eDirection mAttackDirection;

	};
}

