#pragma once
#include "..\\ArkCollectorEngine_SOURCE\acScriptComponent.h"

namespace ac
{
	class ProjectileScriptComponent : public ScriptComponent
	{
	public:
		enum class eEffectType
		{
			Projectile,
			Effect,
			End,
		};
		enum class eDamageType
		{
			Projectile,
			Effect,
			None,
			End,
		};
		ProjectileScriptComponent();
		~ProjectileScriptComponent();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

		virtual void OnCollisionEnter(class ColliderComponent* other) override;
		virtual void OnCollisionStay(class ColliderComponent* other) override;
		virtual void OnCollisionExit(class ColliderComponent* other) override;

		eEffectType GetEffectType() { return mEffectType; }
		void SetEffectType(eEffectType InState) { mEffectType = InState; }
		eDamageType GetDamageType() { return mDamageType; }
		void SetDamageType(eDamageType InState) { mDamageType = InState; }
		float GetDamage() { return mDamage; }
		void SetDamage(float damage) { mDamage = damage; }

	private:
		eEffectType mEffectType;
		eDamageType mDamageType;
		float mDamage;
	};
}