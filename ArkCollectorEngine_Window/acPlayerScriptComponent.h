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
		void setDirection();
		void setState();

		void idle();
		void walk();
		void jump();
		void land();
		void attack();
		void skill01();
		void skill02();
		void skill03();
		void skill04();
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
	};
}

