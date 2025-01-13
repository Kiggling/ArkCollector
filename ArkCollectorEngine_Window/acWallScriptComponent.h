#pragma once
#include "..\\ArkCollectorEngine_SOURCE\acScriptComponent.h"

namespace ac
{
	class WallScriptComponent : public ScriptComponent
	{
	public:
		enum class eState
		{
			Build,
			Destroy,
			End,
		};
		WallScriptComponent();
		~WallScriptComponent();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

		virtual void OnCollisionEnter(class ColliderComponent* other) override;
		virtual void OnCollisionStay(class ColliderComponent* other) override;
		virtual void OnCollisionExit(class ColliderComponent* other) override;

	private:
		void build();
		void destroy();

	private:
		std::wstring directions[4] = { L"Down", L"Up", L"Left", L"Right" };

		float mTime;
		eState mState;
	};
}