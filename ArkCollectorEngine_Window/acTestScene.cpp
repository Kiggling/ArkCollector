#include "acTestScene.h"
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
#include "acScriptComponent.h"

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
		playerCollidier->SetOffset(math::Vector2(-12.0f, -12.0f));

		// Player Stat
		StatComponent* playerStat = mPlayer->AddComponent<StatComponent>();
		playerStat->SetMaxHp(100.0f);
		playerStat->SetMaxMp(100.0f);
		//playerStat->SetHp(playerStat->GetMaxHp());
		playerStat->SetHp(30.0f);
		playerStat->SetMp(playerStat->GetMaxMp());
		playerStat->SetDamage(50.0f);
		playerStat->SetAttackSpeed(1.0f);

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

		Scene::Initialize();
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