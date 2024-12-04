#include "acToolScene.h"
#include "acCameraComponent.h"
#include "acRenderer.h"
#include "acApplication.h"
#include "acCameraScriptComponent.h"
#include "acObject.h"
#include "acTile.h"
#include "acTilemapRendererComponent.h"
#include "acInput.h"
#include "acResources.h"

extern ac::Application application;

namespace ac
{
	ToolScene::ToolScene()
	{
	}
	ToolScene::~ToolScene()
	{
	}
	void ToolScene::Initialize()
	{

		UINT WinWidth = application.GetWidth();
		UINT WinHeight = application.GetHeight();

		GameObject* camera = object::Instantiate<GameObject>(enums::ELayerType::None, math::Vector2(WinWidth/2, WinHeight/2));
		CameraComponent* cameraComp = camera->AddComponent<CameraComponent>();
		CameraScriptComponent* sc = camera->AddComponent<CameraScriptComponent>();
		renderer::mainCamera = cameraComp;

		Scene::Initialize();
	}
	void ToolScene::Update()
	{
		Scene::Update();		
	}
	void ToolScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (Input::GetKeyDown(EKeyCode::LBUTTON))
		{
			math::Vector2 pos = Input::GetMousePosition();
			pos = renderer::mainCamera->GetPositionInToolScene(pos);

			if (pos.x >= 0.f && pos.y >= 0.f)
			{
				int idxX = pos.x / TilemapRendererComponent::TileSize.x;
				int idxY = pos.y / TilemapRendererComponent::TileSize.y;

				Tile* tile = object::Instantiate<Tile>(enums::ELayerType::Tile);
				TilemapRendererComponent* tmr = tile->AddComponent<TilemapRendererComponent>();
				tmr->SetTexture(Resources::Find<graphics::Texture>(L"DungeonTileset"));
				tmr->SetIndex(math::Vector2(13, 4));

				tile->SetIndexPosition(idxX, idxY);


			}

		}
	}
	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		UINT WinWidth = application.GetWidth();
		UINT WinHeight = application.GetHeight();

		UINT numOfWidthLine = 100;
		UINT numOfHeightLine = 100;

		for (size_t i = 0; i < numOfWidthLine; i++)
		{
			math::Vector2 pos = renderer::mainCamera->GetPositionInCameraSpace(math::Vector2(TilemapRendererComponent::TileSize.x*i, 0.f));

			MoveToEx(hdc, pos.x, 0, NULL);
			LineTo(hdc, pos.x, WinHeight);
		}
		for (size_t i = 0; i < numOfHeightLine; i++)
		{
			math::Vector2 pos = renderer::mainCamera->GetPositionInCameraSpace(math::Vector2(0.f, TilemapRendererComponent::TileSize.y*i));

			MoveToEx(hdc, 0, pos.y, NULL);
			LineTo(hdc, WinWidth, pos.y);
		}
	}
	void ToolScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void ToolScene::OnExit()
	{
		Scene::OnExit();
	}
}