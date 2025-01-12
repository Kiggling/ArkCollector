#include "acLamp.h"
#include "acTime.h"
#include "acAnimatorComponent.h"

namespace ac
{
	Lamp::Lamp()
		: mTimer(0.0f)
		, mTimerLimit(20.0f)
		, mbLight(true)
	{
	}
	Lamp::~Lamp()
	{
	}
	void Lamp::Initialize()
	{
		GameObject::Initialize();
	}
	// 타이머로 시간 재다가 시간이 Limit만큼 되면 불 끄기
	void Lamp::Update()
	{
		if (mbLight == true)
			mTimer += Time::DeltaTime();
		if (mTimer >= mTimerLimit)
		{
			GetComponent<AnimatorComponent>()->PlayAnimation(L"Off", true);

			mbLight = false;
		}

		GameObject::Update();
	}
	void Lamp::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Lamp::Render(HDC InHdc)
	{
		GameObject::Render(InHdc);
	}
	// 불을 켜고 끄는 함수
	void Lamp::SetLight(bool light)
	{
		mbLight = light;
		if (light == true)
		{
			mTimer = 0.0f;

			GetComponent<AnimatorComponent>()->PlayAnimation(L"On", true);
		}
		else
		{
			GetComponent<AnimatorComponent>()->PlayAnimation(L"Off", true);
		}
	}
}