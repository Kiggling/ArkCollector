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

		float GetMaxHp() { return mMaxHp; }
		void SetMaxHp(float maxHp) { mMaxHp = maxHp; }
		float GetMaxMp() { return mMaxMp; }
		void SetMaxMp(float maxMp) { mMaxMp = maxMp; }

		float GetHp() { return mHp; }
		void SetHp(float hp) { mHp = hp; }
		float GetMp() { return mMp; }
		void SetMp(float mp) { mMp = mp; }

		float GetDamage() { return mDamage; }
		void SetDamage(float damage) { mDamage = damage; }
		float GetAttackSpeed() { return mAttackSpeed; }
		void SetAttackSpeed(float attackSpeed) { mAttackSpeed = attackSpeed; }

	private:
		float mMaxHp;
		float mMaxMp;

		float mHp;
		float mMp;

		float mDamage;
		float mAttackSpeed;
	};
}