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

extern ac::Application application;

namespace ac
{
	TestScene::TestScene()
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

		// Map
		GameObject* background = object::Instantiate<GameObject>(enums::ELayerType::BackGround);
		background->AddComponent<TransformComponent>();
		SpriteRenderer* sr = background->AddComponent<SpriteRenderer>();
		graphics::Texture* texture = Resources::Find<graphics::Texture>(L"Dungeon");
		sr->SetTexture(texture);

		// Player
		mPlayer = object::Instantiate<Player>(enums::ELayerType::Player);
		object::DontDestroyOnLoad(mPlayer);
		TransformComponent* playerTr = mPlayer->AddComponent<TransformComponent>();
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

		playerTr->SetPosition(math::Vector2(100.0f, 100.0f));
		playerTr->SetWidth(24.0f);
		playerTr->SetHeight(24.0f);

		BoxCollidier2DComponent* playerCollidier = mPlayer->AddComponent<BoxCollidier2DComponent>();
		playerCollidier->SetSize(math::Vector2(playerTr->GetWidth(), playerTr->GetHeight()));

		// Player Stat
		PlayerStatComponent* playerStat = mPlayer->AddComponent<PlayerStatComponent>();
		//playerStat->SetMaxHp(100.0f);
		//playerStat->SetMaxMp(100.0f);
		////playerStat->SetHp(playerStat->GetMaxHp());
		//playerStat->SetHp(30.0f);
		//playerStat->SetMp(playerStat->GetMaxMp());
		//playerStat->SetDamage(50.0f);
		//playerStat->SetAttackSpeed(1.0f);

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

		StatComponent* bossStat = mBoss->AddComponent<StatComponent>();
		bossStat->SetMaxHp(1000.f);
		bossStat->SetHp(1000.f);

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


		bossAnimatorComp->PlayAnimation(L"IdleDown", true);

		Scene::Initialize();

		UIManager::Push(enums::EUIType::HUD);
	}
	void TestScene::Update()
	{
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