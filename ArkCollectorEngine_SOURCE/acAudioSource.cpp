#include "acAudioSource.h"
#include "acTransformComponent.h"
#include "acGameObject.h"
#include "acFmod.h"

namespace ac
{
	AudioSource::AudioSource()
		: Component(enums::EComponentType::AudioSource)
		, mAudioClip(nullptr)
	{
	}
	AudioSource::~AudioSource()
	{
	}
	void AudioSource::Initialize()
	{
	}
	void AudioSource::Update()
	{
	}
	void AudioSource::LateUpdate()
	{
		TransformComponent* tr = GetOwner()->GetComponent<TransformComponent>();
		math::Vector2 pos = tr->GetPosition();

		mAudioClip->Set3DAttributes(pos);
	}
	void AudioSource::Render(HDC hdc)
	{
	}
	void AudioSource::Play(float volume)
	{
		mAudioClip->Play(volume);
	}
	void AudioSource::Stop()
	{
		mAudioClip->Stop();
	}
	void AudioSource::SetLoop(bool loop)
	{
		mAudioClip->SetLoop(loop);
	}
}