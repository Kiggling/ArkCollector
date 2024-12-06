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
				tmr->SetIndex(TilemapRendererComponent::SelectedIndex);

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


LRESULT CALLBACK TileWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		POINT mousePos = {};
		GetCursorPos(&mousePos);
		ScreenToClient(hWnd, &mousePos);

		ac::math::Vector2 mousePositionVector;
		mousePositionVector.x = mousePos.x;
		mousePositionVector.y = mousePos.y;

		int idxX = mousePositionVector.x / ac::TilemapRendererComponent::OriginTileSize.x;
		int idxY = mousePositionVector.y / ac::TilemapRendererComponent::OriginTileSize.y;

		ac::TilemapRendererComponent::SelectedIndex = ac::math::Vector2(idxX, idxY);
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...


		ac::graphics::Texture* texture = ac::Resources::Find<ac::graphics::Texture>(L"DungeonTileset");

		if (texture == nullptr)
			assert(false);

		if (texture->GetTextureType()
			== ac::graphics::Texture::eTextureType::Bmp)
		{
			if (texture->IsAlpha())
			{
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				func.SourceConstantAlpha = 255; // 0(transparent) ~ 255(Opaque)

				AlphaBlend(hdc
					, 0
					, 0
					, texture->GetWidth()
					, texture->GetHeight() 
					, texture->GetHdc()
					, 0, 0
					, texture->GetWidth()
					, texture->GetHeight()
					, func);
			}
			else
			{
				TransparentBlt(hdc
					, 0
					, 0
					, texture->GetWidth()
					, texture->GetHeight()
					, texture->GetHdc()
					, 0, 0
					, texture->GetWidth()
					, texture->GetHeight()
					, RGB(255, 0, 255));
			}
		}
		else if (texture->GetTextureType()
			== ac::graphics::Texture::eTextureType::Png)
		{
			// 투명화시킬 픽셀의 색 범위
			Gdiplus::ImageAttributes imgAtt = {};
			imgAtt.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));

			Gdiplus::Graphics graphics(hdc);

			graphics.DrawImage(texture->GetImage()
				, Gdiplus::Rect
				(
					0, 0
					, texture->GetWidth()
					, texture->GetHeight()
				)
				, 0, 0
				, texture->GetWidth(), texture->GetHeight()
				, Gdiplus::UnitPixel
				, nullptr/*&imgAtt*/);
		}


		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}