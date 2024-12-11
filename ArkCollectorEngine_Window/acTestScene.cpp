#include "acTestScene.h"
#include "acGameObject.h"
#include "acSpriteRendererComponent.h"
#include "acObject.h"
#include "acResources.h"
#include "acTexture.h"

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
		GameObject* background = object::Instantiate<GameObject>(enums::ELayerType::BackGround);
		SpriteRenderer* sr = background->AddComponent<SpriteRenderer>();
		graphics::Texture* texture = Resources::Find<graphics::Texture>(L"SpringFloor");
		sr->SetTexture(texture);

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