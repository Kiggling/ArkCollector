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
		: mTiles{}
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
		renderer::mainCamera = cameraComp;

		Scene::Initialize();
	}
	void ToolScene::Update()
	{
		Scene::Update();

		for (auto it = mTiles.begin(); it != mTiles.end(); )
		{
			math::Vector2 mousePos = Input::GetMousePosition();
			int idxX = mousePos.x / TilemapRendererComponent::TileSize.x;
			int idxY = mousePos.y / TilemapRendererComponent::TileSize.y;
			mousePos.x = idxX * TilemapRendererComponent::TileSize.x;
			mousePos.y = idxY * TilemapRendererComponent::TileSize.y;

			TransformComponent* tr = (*it)->GetComponent<TransformComponent>();
			
			if (fabs(mousePos.x - tr->GetPosition().x) < 0.001f && fabs(mousePos.y - tr->GetPosition().y) < 0.001f)
			{
				if (Input::GetKeyDown(EKeyCode::D))
				{
					(*it)->SetIsDead(true);
					it = mTiles.erase(it);
					continue;
				}
			}

			it++;
		}
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

				mTiles.push_back(tile);
			}
		}
		if (Input::GetKeyDown(EKeyCode::S))
		{
			Save();
		}
		if (Input::GetKeyDown(EKeyCode::L))
		{
			Load();
		}
	}
	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		UINT WinWidth = application.GetWidth();
		UINT WinHeight = application.GetHeight();

		UINT numOfWidthLine = WinWidth / TilemapRendererComponent::TileSize.x;
		UINT numOfHeightLine = WinHeight / TilemapRendererComponent::TileSize.y;

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
	void ToolScene::Save()
	{
		// open a file name
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetSaveFileName(&ofn))
			return;

		FILE* file = nullptr;

		_wfopen_s(&file, szFilePath, L"wt");
		int cnt = 0;
		for (Tile* tile : mTiles)
		{
			TilemapRendererComponent* tmr = tile->GetComponent<TilemapRendererComponent>();
			TransformComponent* tr = tile->GetComponent<TransformComponent>();

			math::Vector2 sourceIndex = tmr->GetIndex();
			math::Vector2 position = tr->GetPosition();

			int x = sourceIndex.x;
			fwrite(&x, sizeof(int), 1, file);
			int y = sourceIndex.y;
			fwrite(&y, sizeof(int), 1, file);
			x = position.x;
			fwrite(&x, sizeof(int), 1, file);
			y = position.y;
			fwrite(&y, sizeof(int), 1, file);

			cnt++;

			if (cnt > 162)
			{
				int a = 0;
			}
		}
		fclose(file);

		wchar_t successMessage[100] = {};
		swprintf_s(successMessage, L"%d개의 타일이 성공적으로 저장되었습니다.", cnt);
		MessageBox(
			NULL,
			successMessage,
			L"알림",                         
			MB_OK | MB_ICONINFORMATION         // 확인 버튼 및 정보 아이콘
		);

	}
	void ToolScene::Load()
	{
		// open a file name
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetSaveFileName(&ofn))
			return;

		FILE* file = nullptr;

		_wfopen_s(&file, szFilePath, L"rt");
		int cnt = 0;
		while(true)
		{
			int idxX = 0;
			int idxY = 0;
			int posX = 0;
			int posY = 0;

			if (cnt >= 163)
			{
				int a = 0;
			}

			if (fread(&idxX, sizeof(int), 1, file) == NULL)
				break;
			if (fread(&idxY, sizeof(int), 1, file) == NULL)
				break;
			if (fread(&posX, sizeof(int), 1, file) == NULL)
				break;
			if (fread(&posY, sizeof(int), 1, file) == NULL)
				break;

			Tile* tile = object::Instantiate<Tile>(enums::ELayerType::Tile, math::Vector2(posX, posY));
			TilemapRendererComponent* tmr = tile->AddComponent<TilemapRendererComponent>();
			tmr->SetTexture(Resources::Find<graphics::Texture>(L"DungeonTileset"));
			tmr->SetIndex(math::Vector2(idxX, idxY));

			mTiles.push_back(tile);
			cnt++;
		}
		fclose(file);

		wchar_t successMessage[100] = {};
		swprintf_s(successMessage, L"%d개의 타일을 불러왔습니다.", cnt);
		MessageBox(
			NULL,
			successMessage,
			L"알림",
			MB_OK | MB_ICONINFORMATION         // 확인 버튼 및 정보 아이콘
		);

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