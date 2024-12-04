#pragma once
#include "CommonInclude.h"
#include "acEntity.h"
#include "acComponent.h"

namespace ac
{
	/* 사용 예시
	* ScriptComponent* sc = gameObj->AddComponent<ScriptComponent>();
	*/
	class ScriptComponent : public Component
	{
	public:
		ScriptComponent();
		~ScriptComponent();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

		virtual void OnCollisionEnter(class ColliderComponent* other);
		virtual void OnCollisionStay(class ColliderComponent* other);
		virtual void OnCollisionExit(class ColliderComponent* other);

	private:
	};
}
