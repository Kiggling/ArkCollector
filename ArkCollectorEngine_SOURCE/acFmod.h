#pragma once
#include "CommonInclude.h"
#include "..\\External\\Include\\Fmod\fmod_studio.hpp"
#include "..\\External\\Include\\Fmod\\fmod.hpp"
#include "..\\External\\Include\\Fmod\\fmod_common.h"
#include "..\\External\\Include\\Fmod\\fmod_codec.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\External\\Library\\Fmod\\Debug\\fmodL_vc.lib")
#pragma comment(lib, "..\\External\\Library\\Fmod\\Debug\\fmodstudioL_vc.lib")
#else
#pragma comment(lib, "..\\External\\Library\\Fmod\\Debug\\fmod_vc.lib")
#pragma comment(lib, "..\\External\\Library\\Fmod\\Release\\fmodstudio_vc.lib")
#endif
namespace ac
{
	using namespace math;
	class Fmod
	{
	public:
		static void Initialize();
		static bool CreateSound(const std::string& path, FMOD::Sound** sound);
		static void SoundPlay(FMOD::Sound* sound, FMOD::Channel** channel, float volume);
		static void Set3DListenerAttributes(const Vector2* pos);
		static void Release();
	private:
		static FMOD::Studio::System* mSystem;
		static FMOD::System* mCoreSystem;
	};
}

// 사용예시
// 1. LoadResources.h - Resources::Load<AudioClip>(L"PlayerJump", L"..\\Content\\Sound\\Player\\Player_Jump.wav");
// 2. AudioSource* playerAs = mPlayer->AddComponent<AudioSource>();
//	  AudioClip* playerAc = Resources::Find<AudioClip>(L"PlayerJump");
//    playerAs->SetClip(playerAc);
// 3. playerAs->Play(volume); 하면 사운드 출력 (volume은 0.0f ~ 1.0f)
//