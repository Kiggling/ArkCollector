#pragma once
#include "CommonInclude.h"

namespace ac
{
	class Time
	{
	public:
		void Initialize();
		void Tick();
		void Render(HDC hdc);

		float DeltaTime() { return mDeltaTime; }

	private:
		LARGE_INTEGER mCpuFrequency;
		LARGE_INTEGER mPrevFrequency;
		LARGE_INTEGER mCurrentFrequency;

		float mDeltaTime;
	};
}

