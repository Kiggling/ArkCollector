#pragma once
#include "..\\ArkCollectorEngine_SOURCE\\acResources.h"
#include "..\\ArkCollectorEngine_SOURCE\\acTexture.h"

namespace ac
{
	void LoadResources()
	{
		//Resources::Load<graphics::Texture>();
		Resources::Load<graphics::Texture>(L"DungeonTileset", L"..\\Content\\Dungeon_Tileset\\Png\\DungeonTileset.png");
		Resources::Load<graphics::Texture>(L"SpringFloor", L"..\\Content\\Dungeon_Tileset\\Png\\SpringFloor.bmp");
		Resources::Load<graphics::Texture>(L"Dungeon", L"..\\Content\\Dungeon_Tileset\\Dungeon.bmp");


		// UI
		Resources::Load<graphics::Texture>(L"HPBAR", L"..\\Content\\RPG_UI\\HUD Health Bar\\HUDHealthBar.png");
	}
}