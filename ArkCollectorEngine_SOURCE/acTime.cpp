#include "acTime.h"

namespace ac
{
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mCurrentFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	float Time::mDeltaTime = 0.0f;

	void Time::Initialize()
	{
		// cpu의 초당 주파수를 mCpuFrequency에 받아온다.
		QueryPerformanceFrequency(&mCpuFrequency);

		// 프로그램이 시작된 시점의 cpu 클럭 수를 mPrevFrequency에 받아온다.
		QueryPerformanceCounter(&mPrevFrequency);
	}
	void Time::Update()
	{
		QueryPerformanceCounter(&mCurrentFrequency);

		float frequencyDifference = static_cast<float>(mCurrentFrequency.QuadPart - mPrevFrequency.QuadPart);

		mDeltaTime = frequencyDifference / static_cast<float>(mCpuFrequency.QuadPart);

		mPrevFrequency.QuadPart = mCurrentFrequency.QuadPart;
	}
	void Time::Render(HDC hdc)
	{

	}
}