#pragma once
#include "acComponent.h"
#include "acAudioClip.h"

namespace ac
{
	class AudioSource : public Component
	{
	public:
		AudioSource();
		~AudioSource();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void Play(float volume = 1.0f);
		void Stop();
		void SetLoop(bool loop);

		void SetClip(AudioClip* clip) { mAudioClip = clip; }
		AudioClip* GetClip() { return mAudioClip; }

	private:
		AudioClip* mAudioClip;
	};
}
