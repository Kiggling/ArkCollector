#pragma once
#include "..\\ArkCollectorEngine_SOURCE\acScriptComponent.h"

namespace ac
{
	class PlayerScriptComponent : public ScriptComponent
	{
	public:
		enum class eState
		{
			Idle,
			Walk,
			Jump,
			Land,
			Attack,
			Skill01,
			Skill02,
			Skill03,
			Skill04,
			item01,
			item02,
			item03,
			item04,
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

		enum class eAttackType
		{
			None,
			BasicAttack,
			Skill01,
			Skill02,
			Skill03,
			Skill04,
			End,
		};

		PlayerScriptComponent();
		~PlayerScriptComponent();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

		virtual void OnCollisionEnter(class ColliderComponent* other) override;
		virtual void OnCollisionStay(class ColliderComponent* other) override;
		virtual void OnCollisionExit(class ColliderComponent* other) override;

		bool GetInvincible() { return mbinvincible; };

	private:
		void setTimer();
		void setDirection();
		void setState();
		void useItem();

		void idle();
		void walk();
		void jump();
		void land();
		void isAttacking();
		void skill01();
		void skill02();
		void skill03();
		void skill04();
		void item01();
		void item02();
		void item03();
		void item04();
		void hurt();
		void death();

	private:
		eState mState;
		eDirection mAnimationDirection;
		class AnimatorComponent* mAnimatorComponent;
		
		bool mbAttack;
		eDirection mAttackDirection;
		eAttackType mAttackType;

		bool mbShield;
		bool mbinvincible;
		class Shield* mShield;

		class AudioSource* mAudioSource;

		float mSkillTimer[4];

		float mItemTimer[4];
	};
}

