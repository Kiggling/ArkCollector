#pragma once
#include "..\\ArkCollectorEngine_SOURCE\\acGameObject.h"

namespace ac 
{
	// Lamp Ŭ����
	// mTimer�� mTimerLimit�� �����ϸ� ���� ����
	// ���� ������ mbLight�� true, ������ false
	//
	class Lamp : public GameObject
	{
	public:
		Lamp();
		~Lamp();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

		void SetTimerLimit(float timerLimit) { mTimerLimit = timerLimit; }

		bool GetLight() { return mbLight; }
		void SetLight(bool light);

	private:
		void playAudio(const std::wstring& audioName, float volume = 1.0f);

	private:
		float mTimer;
		float mTimerLimit;

		bool mbLight;
	};
}

