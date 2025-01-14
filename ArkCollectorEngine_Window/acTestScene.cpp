#include "acTestScene.h"
#include "acGameObject.h"
#include "acSpriteRendererComponent.h"
#include "acObject.h"
#include "acResources.h"
#include "acTexture.h"
#include "acUIManager.h"
#include "acGameObject.h"
#include "acPlayer.h"
#include "acPlayerScriptComponent.h"
#include "acCameraComponent.h"
#include "acTransformComponent.h"
#include "acObject.h"
#include "acRenderer.h"
#include "acTexture.h"
#include "acResources.h"
#include "acAnimatorComponent.h"
#include "acProjectile.h"
#include "acSpriteRendererComponent.h"
#include "acBoxCollidier2DComponent.h"
#include "acProjectileScriptComponent.h"
#include "acStatComponent.h"
#include "acPlayerStatComponent.h"
#include "acScriptComponent.h"
#include "acBoss.h"
#include "acBossScriptComponent.h"
#include "acApplication.h"
#include "acBossStatComponent.h"
#include "acAudioClip.h"
#include "acAudioListener.h"
#include "acAudioSource.h"
#include "acLamp.h"

extern ac::Application application;

namespace ac
{
	TestScene::TestScene()
		: mBoss(nullptr)
		, mPlayer(nullptr)
	{
	}
	TestScene::~TestScene()
	{
	}
	void TestScene::Initialize()
	{
		//GameObject* camera = object::Instantiate<GameObject>(enums::ELayerType::Particle, math::Vector2());
		//CameraComponent* cameraComp = camera->AddComponent<CameraComponent>();
		//renderer::mainCamera = cameraComp;

		mapInit();
		playerInit();
		bossInit();

		// test Collider
		Player* testPlayer = object::Instantiate<Player>(enums::ELayerType::Player);
		testPlayer->SetName(L"testPlayer");
		TransformComponent* testPlayerTr = testPlayer->AddComponent<TransformComponent>();
		ScriptComponent* testPlScript = testPlayer->AddComponent<ScriptComponent>();
		testPlayerTr->SetPosition(math::Vector2(100.0f, 200.0f));
		testPlayerTr->SetWidth(24.0f);
		testPlayerTr->SetHeight(24.0f);
		BoxCollidier2DComponent* testPlayerCollidier = testPlayer->AddComponent<BoxCollidier2DComponent>();
		testPlayerCollidier->SetSize(math::Vector2(testPlayerTr->GetWidth(), testPlayerTr->GetHeight()));
		StatComponent* testPlayerStat = testPlayer->AddComponent<StatComponent>();
		testPlayerStat->SetName(L"testPlayerStat");
		testPlayerStat->SetHp(100.0f);
		testPlayerStat->SetMp(100.0f);
		testPlayerStat->SetDamage(5.0f);
		testPlayerStat->SetAttackSpeed(1.0f);

		// Lamps
		math::Vector2 lampsLocation[] = { math::Vector2(400.0f, 300.0f), math::Vector2(1040.0f, 300.0f), math::Vector2(720.0f, 450.0f), math::Vector2(400.0f, 600.0f), math::Vector2(1040.0f, 600.0f) };
		srand(time(NULL));
		for (size_t i = 0; i < 5; i++)
		{
			mLamps[i] = object::Instantiate<Lamp>(enums::ELayerType::Tile);
			mLamps[i]->SetTimerLimit(20.0f + (rand() % 30));

			TransformComponent* lampTr = mLamps[i]->AddComponent<TransformComponent>();
			lampTr->SetPosition(lampsLocation[i]);
			lampTr->SetWidth(24.0f);
			lampTr->SetHeight(24.0f);

			graphics::Texture* lampTexture = Resources::Find<graphics::Texture>(L"LampOn");
			AnimatorComponent* lampAnimatorComp = mLamps[i]->AddComponent<AnimatorComponent>();
			lampAnimatorComp->CreateAnimation(L"On", lampTexture, math::Vector2(0.0f, 0.0f), math::Vector2(32.0f, 32.0f), math::Vector2::Zero, 3, 0.2f);
			lampTexture = Resources::Find<graphics::Texture>(L"LampOff");
			lampAnimatorComp->CreateAnimation(L"Off", lampTexture, math::Vector2(0.0f, 0.0f), math::Vector2(32.0f, 32.0f), math::Vector2::Zero, 3, 0.2f);

			lampAnimatorComp->PlayAnimation(L"On", true);

			//LampScriptComponent* lampScript = mLamps[i]->AddComponent<LampScriptComponent>();

			BoxCollidier2DComponent* lampCollidier = mLamps[i]->AddComponent<BoxCollidier2DComponent>();
			lampCollidier->SetSize(math::Vector2(lampTr->GetWidth(), lampTr->GetHeight()));

			AudioSource* lampAs = mLamps[i]->AddComponent<AudioSource>();
			AudioClip* lampAc = Resources::Find<AudioClip>(L"LampOnSound");
			lampAs->SetClip(lampAc);
		}

		// Layer에서 제일 위에 mCover를 둬서 반투명 구현
		mCover = object::Instantiate<GameObject>(enums::ELayerType::Cover);
		mCover->AddComponent<TransformComponent>();
		SpriteRenderer* coverSr = mCover->AddComponent<SpriteRenderer>();
		graphics::Texture* coverTexture = Resources::Find<graphics::Texture>(L"Cover_5");
		coverSr->SetTexture(coverTexture);

		// 플레이어가 DontDestroyOnLoad에 있어서 플레이어를 가릴 커버 구현
		mCoverDontDestroyOnLoad = object::Instantiate<GameObject>(enums::ELayerType::Cover);
		object::DontDestroyOnLoad(mCoverDontDestroyOnLoad);
		mCoverDontDestroyOnLoad->AddComponent<TransformComponent>();
		SpriteRenderer* coverDontDestroyOnLoadSr = mCoverDontDestroyOnLoad->AddComponent<SpriteRenderer>();
		graphics::Texture* coverDontDestroyOnLoadTexture = Resources::Find<graphics::Texture>(L"Cover_5");
		coverDontDestroyOnLoadSr->SetTexture(coverTexture);


		Scene::Initialize();

		UIManager::Push(enums::EUIType::HUD);
	}
	void TestScene::mapInit()
	{
		// Map
		GameObject* background = object::Instantiate<GameObject>(enums::ELayerType::BackGround);
		background->AddComponent<TransformComponent>();
		SpriteRenderer* sr = background->AddComponent<SpriteRenderer>();
		graphics::Texture* texture = Resources::Find<graphics::Texture>(L"Dungeon");
		sr->SetTexture(texture);

		AudioSource* backgroundAs = background->AddComponent<AudioSource>();
		AudioClip* backgroundAc = Resources::Find<AudioClip>(L"DungeonSound");
		backgroundAs->SetClip(backgroundAc);
		backgroundAs->SetLoop(true);
		backgroundAs->Play(0.5f);
	}
	void TestScene::playerInit()
	{
		// Player
		mPlayer = object::Instantiate<Player>(enums::ELayerType::Player);
		object::DontDestroyOnLoad(mPlayer);
		mPlayer->AddComponent<AudioListener>();
		TransformComponent* playerTr = mPlayer->AddComponent<TransformComponent>();
		AudioSource* playerAs = mPlayer->AddComponent<AudioSource>();
		AudioClip* playerAc = Resources::Find<AudioClip>(L"PlayerArrowSound");
		playerAs->SetClip(playerAc);
		PlayerScriptComponent* plScript = mPlayer->AddComponent<PlayerScriptComponent>();

		graphics::Texture* playerTexture = Resources::Find<graphics::Texture>(L"PlayerIdleDown");
		AnimatorComponent* playerAnimatorComp = mPlayer->AddComponent<AnimatorComponent>();
		playerAnimatorComp->CreateAnimation(L"IdleDown", playerTexture, math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 6, 0.2f);

		playerTexture = Resources::Find<graphics::Texture>(L"PlayerIdleLeft");
		playerAnimatorComp->CreateAnimation(L"IdleLeft", playerTexture, math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 6, 0.2f);
		playerTexture = Resources::Find<graphics::Texture>(L"PlayerIdleRight");
		playerAnimatorComp->CreateAnimation(L"IdleRight", playerTexture, math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 6, 0.2f);
		playerTexture = Resources::Find<graphics::Texture>(L"PlayerIdleUp");
		playerAnimatorComp->CreateAnimation(L"IdleUp", playerTexture, math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 6, 0.2f);

		playerTexture = Resources::Find<graphics::Texture>(L"PlayerWalkDown");
		playerAnimatorComp->CreateAnimation(L"WalkDown", playerTexture, math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 6, 0.2f);
		playerTexture = Resources::Find<graphics::Texture>(L"PlayerWalkLeft");
		playerAnimatorComp->CreateAnimation(L"WalkLeft", playerTexture, math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 6, 0.2f);
		playerTexture = Resources::Find<graphics::Texture>(L"PlayerWalkRight");
		playerAnimatorComp->CreateAnimation(L"WalkRight", playerTexture, math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 6, 0.2f);
		playerTexture = Resources::Find<graphics::Texture>(L"PlayerWalkUp");
		playerAnimatorComp->CreateAnimation(L"WalkUp", playerTexture, math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 6, 0.2f);

		playerTexture = Resources::Find<graphics::Texture>(L"PlayerAttackDown");
		playerAnimatorComp->CreateAnimation(L"AttackDown", playerTexture, math::Vector2(48.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 11, 0.1f);
		playerTexture = Resources::Find<graphics::Texture>(L"PlayerAttackLeft");
		playerAnimatorComp->CreateAnimation(L"AttackLeft", playerTexture, math::Vector2(48.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 11, 0.1f);
		playerTexture = Resources::Find<graphics::Texture>(L"PlayerAttackRight");
		playerAnimatorComp->CreateAnimation(L"AttackRight", playerTexture, math::Vector2(48.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 11, 0.1f);
		playerTexture = Resources::Find<graphics::Texture>(L"PlayerAttackUp");
		playerAnimatorComp->CreateAnimation(L"AttackUp", playerTexture, math::Vector2(48.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 11, 0.1f);

		playerTexture = Resources::Find<graphics::Texture>(L"PlayerJumpDown");
		playerAnimatorComp->CreateAnimation(L"JumpDown", playerTexture, math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 8, 0.1f);
		playerTexture = Resources::Find<graphics::Texture>(L"PlayerJumpLeft");
		playerAnimatorComp->CreateAnimation(L"JumpLeft", playerTexture, math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 8, 0.1f);
		playerTexture = Resources::Find<graphics::Texture>(L"PlayerJumpRight");
		playerAnimatorComp->CreateAnimation(L"JumpRight", playerTexture, math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 8, 0.1f);
		playerTexture = Resources::Find<graphics::Texture>(L"PlayerJumpUp");
		playerAnimatorComp->CreateAnimation(L"JumpUp", playerTexture, math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 8, 0.1f);

		playerTexture = Resources::Find<graphics::Texture>(L"PlayerHurtDown");
		playerAnimatorComp->CreateAnimation(L"HurtDown", playerTexture, math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 4, 0.1f);
		playerTexture = Resources::Find<graphics::Texture>(L"PlayerHurtLeft");
		playerAnimatorComp->CreateAnimation(L"HurtLeft", playerTexture, math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 4, 0.1f);
		playerTexture = Resources::Find<graphics::Texture>(L"PlayerHurtRight");
		playerAnimatorComp->CreateAnimation(L"HurtRight", playerTexture, math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 4, 0.1f);
		playerTexture = Resources::Find<graphics::Texture>(L"PlayerHurtUp");
		playerAnimatorComp->CreateAnimation(L"HurtUp", playerTexture, math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 4, 0.1f);

		playerTexture = Resources::Find<graphics::Texture>(L"PlayerDeathDown");
		playerAnimatorComp->CreateAnimation(L"DeathDown", playerTexture, math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 8, 0.1f);
		playerTexture = Resources::Find<graphics::Texture>(L"PlayerDeathLeft");
		playerAnimatorComp->CreateAnimation(L"DeathLeft", playerTexture, math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 8, 0.1f);
		playerTexture = Resources::Find<graphics::Texture>(L"PlayerDeathRight");
		playerAnimatorComp->CreateAnimation(L"DeathRight", playerTexture, math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 8, 0.1f);
		playerTexture = Resources::Find<graphics::Texture>(L"PlayerDeathUp");
		playerAnimatorComp->CreateAnimation(L"DeathUp", playerTexture, math::Vector2(0.0f, 0.0f), math::Vector2(48.0f, 48.0f), math::Vector2::Zero, 8, 0.1f);

		playerAnimatorComp->PlayAnimation(L"IdleDown", true);

		playerTr->SetPosition(math::Vector2(400.0f, 400.0f));
		playerTr->SetWidth(24.0f);
		playerTr->SetHeight(24.0f);

		BoxCollidier2DComponent* playerCollidier = mPlayer->AddComponent<BoxCollidier2DComponent>();
		playerCollidier->SetSize(math::Vector2(playerTr->GetWidth(), playerTr->GetHeight()));

		// Player Stat
		PlayerStatComponent* playerStat = mPlayer->AddComponent<PlayerStatComponent>();
		playerStat->SetMaxHp(100.0f);
		playerStat->SetMaxMp(100.0f);
		//playerStat->SetHp(playerStat->GetMaxHp());
		playerStat->SetHp(100.0f);
		playerStat->SetMp(playerStat->GetMaxMp());
		playerStat->SetDamage(50.0f);
		playerStat->SetAttackSpeed(1.0f);
	}
	void TestScene::bossInit()
	{
		// Boss
		mBoss = object::Instantiate<Boss>(enums::ELayerType::Boss);
		TransformComponent* bossTr = mBoss->AddComponent<TransformComponent>();
		bossTr->SetPosition(math::Vector2(700.0f, 400.0f));
		bossTr->SetWidth(40.0f);
		bossTr->SetHeight(60.0f);

		BossScriptComponent* bossScript = mBoss->AddComponent<BossScriptComponent>();
		bossScript->SetTarget(mPlayer);

		BoxCollidier2DComponent* bossCollidier = mBoss->AddComponent<BoxCollidier2DComponent>();
		bossCollidier->SetSize(math::Vector2(bossTr->GetWidth(), bossTr->GetHeight()));

		BossStatComponent* bossStat = mBoss->AddComponent<BossStatComponent>();

		AnimatorComponent* bossAnimatorComp = mBoss->AddComponent<AnimatorComponent>();
		graphics::Texture* bossTexture = Resources::Find<graphics::Texture>(L"BossIdleDown");
		bossAnimatorComp->CreateAnimation(L"IdleDown", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 7, 0.2f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossIdleLeft");
		bossAnimatorComp->CreateAnimation(L"IdleLeft", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 7, 0.2f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossIdleRight");
		bossAnimatorComp->CreateAnimation(L"IdleRight", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 7, 0.2f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossIdleUp");
		bossAnimatorComp->CreateAnimation(L"IdleUp", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 7, 0.2f);

		bossTexture = Resources::Find<graphics::Texture>(L"BossWalkDown");
		bossAnimatorComp->CreateAnimation(L"WalkDown", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 8, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossWalkLeft");
		bossAnimatorComp->CreateAnimation(L"WalkLeft", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(96.0f, 96.0f), math::Vector2::Zero, 8, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossWalkRight");
		bossAnimatorComp->CreateAnimation(L"WalkRight", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(96.0f, 96.0f), math::Vector2::Zero, 8, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossWalkUp");
		bossAnimatorComp->CreateAnimation(L"WalkUp", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 8, 0.1f);

		bossTexture = Resources::Find<graphics::Texture>(L"BossJumpDown");
		bossAnimatorComp->CreateAnimation(L"JumpDown", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 5, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossJumpLeft");
		bossAnimatorComp->CreateAnimation(L"JumpLeft", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 5, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossJumpRight");
		bossAnimatorComp->CreateAnimation(L"JumpRight", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 5, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossJumpUp");
		bossAnimatorComp->CreateAnimation(L"JumpUp", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 5, 0.1f);

		bossTexture = Resources::Find<graphics::Texture>(L"BossLandDown");
		bossAnimatorComp->CreateAnimation(L"LandDown", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 4, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossLandLeft");
		bossAnimatorComp->CreateAnimation(L"LandLeft", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 4, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossLandRight");
		bossAnimatorComp->CreateAnimation(L"LandRight", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 4, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossLandUp");
		bossAnimatorComp->CreateAnimation(L"LandUp", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 4, 0.1f);

		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack01Down");
		bossAnimatorComp->CreateAnimation(L"Attack01Down", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 7, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack01Left");
		bossAnimatorComp->CreateAnimation(L"Attack01Left", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 7, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack01Right");
		bossAnimatorComp->CreateAnimation(L"Attack01Right", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 7, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack01Up");
		bossAnimatorComp->CreateAnimation(L"Attack01Up", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 7, 0.1f);

		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack02Down");
		bossAnimatorComp->CreateAnimation(L"Attack02Down", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 13, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack02Left");
		bossAnimatorComp->CreateAnimation(L"Attack02Left", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 13, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack02Right");
		bossAnimatorComp->CreateAnimation(L"Attack02Right", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 13, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack02Up");
		bossAnimatorComp->CreateAnimation(L"Attack02Up", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 13, 0.1f);

		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack03Down");
		bossAnimatorComp->CreateAnimation(L"Attack03Down", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 7, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack03Left");
		bossAnimatorComp->CreateAnimation(L"Attack03Left", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 7, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack03Right");
		bossAnimatorComp->CreateAnimation(L"Attack03Right", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 7, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack03Up");
		bossAnimatorComp->CreateAnimation(L"Attack03Up", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 7, 0.1f);

		bossTexture = Resources::Find<graphics::Texture>(L"BossHurtDown");
		bossAnimatorComp->CreateAnimation(L"HurtDown", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 4, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossHurtLeft");
		bossAnimatorComp->CreateAnimation(L"HurtLeft", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 4, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossHurtRight");
		bossAnimatorComp->CreateAnimation(L"HurtRight", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 4, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossHurtUp");
		bossAnimatorComp->CreateAnimation(L"HurtUp", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 4, 0.1f);

		bossTexture = Resources::Find<graphics::Texture>(L"BossDeathDown");
		bossAnimatorComp->CreateAnimation(L"DeathDown", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 9, 0.2f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossDeathLeft");
		bossAnimatorComp->CreateAnimation(L"DeathLeft", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 9, 0.2f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossDeathRight");
		bossAnimatorComp->CreateAnimation(L"DeathRight", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 9, 0.2f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossDeathUp");
		bossAnimatorComp->CreateAnimation(L"DeathUp", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 9, 0.2f);

		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack01Down");
		bossAnimatorComp->CreateAnimation(L"Attack01HalfLeftDown", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 4, 0.1f);
		bossAnimatorComp->CreateAnimation(L"Attack01HalfRightDown", bossTexture, math::Vector2(320.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 3, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack01Left");
		bossAnimatorComp->CreateAnimation(L"Attack01HalfLeftLeft", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 4, 0.1f);
		bossAnimatorComp->CreateAnimation(L"Attack01HalfRightLeft", bossTexture, math::Vector2(320.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 3, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack01Right");
		bossAnimatorComp->CreateAnimation(L"Attack01HalfLeftRight", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 4, 0.1f);
		bossAnimatorComp->CreateAnimation(L"Attack01HalfRightRight", bossTexture, math::Vector2(320.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 3, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack01Up");
		bossAnimatorComp->CreateAnimation(L"Attack01HalfLeftUp", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 4, 0.1f);
		bossAnimatorComp->CreateAnimation(L"Attack01HalfRightUp", bossTexture, math::Vector2(320.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 3, 0.1f);

		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack01Down");
		bossAnimatorComp->CreateAnimation(L"Attack01SwordUpDown", bossTexture, math::Vector2(320.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 1, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack01Left");
		bossAnimatorComp->CreateAnimation(L"Attack01SwordUpLeft", bossTexture, math::Vector2(320.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 1, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack01Right");
		bossAnimatorComp->CreateAnimation(L"Attack01SwordUpRight", bossTexture, math::Vector2(320.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 1, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack01Up");
		bossAnimatorComp->CreateAnimation(L"Attack01SwordUpUp", bossTexture, math::Vector2(320.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 1, 0.1f);

		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack03Down");
		bossAnimatorComp->CreateAnimation(L"Attack03HalfLeftDown", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 5, 0.1f);
		bossAnimatorComp->CreateAnimation(L"Attack03HalfRightDown", bossTexture, math::Vector2(320.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 3, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack03Left");
		bossAnimatorComp->CreateAnimation(L"Attack03HalfLeftLeft", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 5, 0.1f);
		bossAnimatorComp->CreateAnimation(L"Attack03HalfRightLeft", bossTexture, math::Vector2(320.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 3, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack03Right");
		bossAnimatorComp->CreateAnimation(L"Attack03HalfLeftRight", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 5, 0.1f);
		bossAnimatorComp->CreateAnimation(L"Attack03HalfRightRight", bossTexture, math::Vector2(320.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 3, 0.1f);
		bossTexture = Resources::Find<graphics::Texture>(L"BossAttack03Up");
		bossAnimatorComp->CreateAnimation(L"Attack03HalfLeftUp", bossTexture, math::Vector2(0.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 5, 0.1f);
		bossAnimatorComp->CreateAnimation(L"Attack03HalfRightUp", bossTexture, math::Vector2(320.0f, 0.0f), math::Vector2(80.0f, 80.0f), math::Vector2::Zero, 3, 0.1f);

		bossAnimatorComp->PlayAnimation(L"IdleDown", true);
	}
	void TestScene::Update()
	{
		// lampCount = 램프가 몇 개 켜져있는지 저장하는 변수
		int lampCount = 0;
		for (size_t i = 0; i < 5; i++)
		{
			if (mLamps[i]->GetLight() == true)
			{
				lampCount++;
			}
		}
		if (lampCount == 0) // 램프가 다 꺼지면 플레이어 사망
		{
			mPlayer->GetComponent<PlayerStatComponent>()->SetHp(0.0f);
		}

		// 켜져있는 램프 개수에 따라 Cover의 투명도 설정
		SpriteRenderer* coverSr = mCover->GetComponent<SpriteRenderer>();
		graphics::Texture* coverTexture = Resources::Find<graphics::Texture>(L"Cover_" + std::to_wstring(lampCount));
		coverSr->SetTexture(coverTexture);

		SpriteRenderer* coverDontDestroyOnLoadSr = mCoverDontDestroyOnLoad->GetComponent<SpriteRenderer>();
		graphics::Texture* coverDontDestroyOnLoadTexture = Resources::Find<graphics::Texture>(L"Cover_" + std::to_wstring(lampCount));
		coverDontDestroyOnLoadSr->SetTexture(coverDontDestroyOnLoadTexture);

		Scene::Update();
	}
	void TestScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TestScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void TestScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void TestScene::OnExit()
	{
		Scene::OnExit();
	}
}