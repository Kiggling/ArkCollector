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
	// Ÿ�̸ӷ� �ð� ��ٰ� �ð��� Limit��ŭ �Ǹ� �� ����
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
	// ���� �Ѱ� ���� �Լ�
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