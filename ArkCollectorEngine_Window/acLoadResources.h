#pragma once
#include "..\\ArkCollectorEngine_SOURCE\\acResources.h"
#include "..\\ArkCollectorEngine_SOURCE\\acTexture.h"

namespace ac
{
	void LoadResources()
	{
		//Resources::Load<graphics::Texture>();
		Resources::Load<graphics::Texture>(L"DungeonTileset", L"..\\Content\\Dungeon_Tileset\\Png\\DungeonTileset.png");
	}
}