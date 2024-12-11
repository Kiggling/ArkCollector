#pragma once
#include "..\\ArkCollectorEngine_SOURCE\\acScene.h"
#include "acTile.h"

namespace ac
{
	class ToolScene : public Scene
	{
	public:
		ToolScene();
		~ToolScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void OnEnter() override;
		void OnExit() override;


		void Save();
		void Load();
		void SaveAsBmp();
	private:
		bool saveBitmapToFile(HBITMAP hBitmap, HDC hDC, LPCWSTR filename);
	private:
		std::vector<Tile*> mTiles;
		bool mbShowLine;
	};
}
LRESULT CALLBACK TileWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);