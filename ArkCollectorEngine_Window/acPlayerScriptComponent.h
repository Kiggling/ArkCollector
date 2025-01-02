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

	private:
		void setTimer();
		void setDirection();
		void setState();
		void useItem();

		void idle();
		void walk();
		void jump();
		void land();
		void attack();
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
		eDirection mDirection;
		class AnimatorComponent* mAnimatorComponent;
		
		bool mbAttack;
		eDirection mAttackDirection;
		eAttackType mAttackType;

		bool mbShield;
		class Shield* mShield;

		bool mbSkill01;
		float mSkill01Cooldown;
		float mSkill01Timer;

		bool mbSkill02;
		float mSkill02Cooldown;
		float mSkill02Timer;

		bool mbSkill03;
		float mSkill03Cooldown;
		float mSkill03Timer;

		bool mbSkill04;
		float mSkill04Cooldown;
		float mSkill04Timer;

		bool mbItem01;
		float mItem01Cooldown;
		float mItem01Timer;

		bool mbItem02;
		float mItem02Cooldown;
		float mItem02Timer;

		bool mbItem03;
		float mItem03Cooldown;
		float mItem03Timer;

		bool mbItem04;
		float mItem04Cooldown;
		float mItem04Timer;
	};
}

