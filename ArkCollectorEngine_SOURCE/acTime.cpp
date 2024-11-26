#include "acTime.h"

namespace ac
{
	void Time::Initialize()
	{
		// cpu�� �ʴ� ���ļ��� mCpuFrequency�� �޾ƿ´�.
		QueryPerformanceFrequency(&mCpuFrequency);

		// ���α׷��� ���۵� ������ cpu Ŭ�� ���� mPrevFrequency�� �޾ƿ´�.
		QueryPerformanceCounter(&mPrevFrequency);
	}
	void Time::Tick()
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