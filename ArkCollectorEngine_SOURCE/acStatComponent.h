#pragma once
#include "acComponent.h"

namespace ac
{
	class StatComponent : public Component
	{
	public:
		StatComponent();
		~StatComponent();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

		float GetHp() { return mHp; }
		void SetHp(float hp) { mHp = hp; }
		float GetMp() { return mMp; }
		void SetMp(float mp) { mMp = mp; }

		float GetDamage() { return mDamage; }
		void SetDamage(float damage) { mDamage = damage; }
		float GetAttackSpeed() { return mAttackSpeed; }
		void SetAttackSpeed(float attackSpeed) { mAttackSpeed = attackSpeed; }

	private:
		float mHp;
		float mMp;

		float mDamage;
		float mAttackSpeed;
	};
}