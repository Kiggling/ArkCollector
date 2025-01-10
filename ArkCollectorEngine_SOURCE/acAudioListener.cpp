#include "acAudioListener.h"
#include "acTransformComponent.h"
#include "acGameObject.h"
#include "acFmod.h"

namespace ac
{
	AudioListener::AudioListener()
		: Component(enums::EComponentType::AudioListener)
	{
	}
	AudioListener::~AudioListener()
	{
	}
	void AudioListener::Initialize()
	{
	}
	void AudioListener::Update()
	{
	}
	void AudioListener::LateUpdate()
	{
		TransformComponent* tr = GetOwner()->GetComponent<TransformComponent>();
		math::Vector2 pos = tr->GetPosition();

		Fmod::Set3DListenerAttributes(&pos);
	}
	void AudioListener::Render(HDC hdc)
	{
	}
}