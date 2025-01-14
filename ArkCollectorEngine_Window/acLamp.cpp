#include "acLamp.h"
#include "acTime.h"
#include "acAnimatorComponent.h"
#include "acAudioSource.h"
#include "acAudioClip.h"
#include "acResources.h"

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
		if (mbLight == true && mTimer >= mTimerLimit)
		{
			GetComponent<AnimatorComponent>()->PlayAnimation(L"Off", true);
			playAudio(L"LampOffSound");

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
			playAudio(L"LampOnSound", 0.5f);
		}
		else
		{
			GetComponent<AnimatorComponent>()->PlayAnimation(L"Off", true);
			playAudio(L"LampOffSound");
		}
	}
	void Lamp::playAudio(const std::wstring& audioName, float volume)
	{
		AudioSource* as = GetComponent<AudioSource>();
		AudioClip* ac = Resources::Find<AudioClip>(audioName);
		as->SetClip(ac);
		as->Play(volume);
	}
}