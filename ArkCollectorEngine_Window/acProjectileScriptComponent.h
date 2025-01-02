#pragma once
#include "..\\ArkCollectorEngine_SOURCE\acScriptComponent.h"

namespace ac
{
	class ProjectileScriptComponent : public ScriptComponent
	{
	public:
		ProjectileScriptComponent();
		~ProjectileScriptComponent();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

		virtual void OnCollisionEnter(class ColliderComponent* other) override;
		virtual void OnCollisionStay(class ColliderComponent* other) override;
		virtual void OnCollisionExit(class ColliderComponent* other) override;

		float GetDamage() { return mDamage; }
		void SetDamage(float damage) { mDamage = damage; }

	private:
		float mDamage;
	};
}