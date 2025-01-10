#include "acAudioSource.h"
#include "acTransformComponent.h"
#include "acGameObject.h"
#include "acFmod.h"

namespace ac
{
	AudioSource::AudioSource()
		: Component(enums::EComponentType::AudioSource)
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
	void AudioSource::Play()
	{
		mAudioClip->Play();
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