#pragma once
#include "..\\ArkCollectorEngine_SOURCE\\acGameObject.h"

namespace ac 
{
	// Lamp 클래스
	// mTimer가 mTimerLimit에 도달하면 불이 꺼짐
	// 불이 켜지면 mbLight는 true, 꺼지면 false
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

		float GetTimerLimit() { return mTimerLimit; }
		void SetTimerLimit(float timerLimit) { mTimerLimit = timerLimit; }
		float GetTimer() { return mTimer; }
		bool GetLight() { return mbLight; }
		void SetLight(bool light);
		bool GetSafe() { return mbSafe; }
		void SetSafe(bool safe) { mbSafe = safe; }

	private:
		void playAudio(const std::wstring& audioName, float volume = 1.0f);

	private:
		float mTimer;
		float mTimerLimit;

		bool mbLight;
		bool mbSafe;
	};
}

