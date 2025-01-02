#pragma once
#include "..\\ArkCollectorEngine_SOURCE\\acResources.h"
#include "..\\ArkCollectorEngine_SOURCE\\acTexture.h"

namespace ac
{
	void LoadResources()
	{
		//Resources::Load<graphics::Texture>();

		// Scene
		Resources::Load<graphics::Texture>(L"DungeonTileset", L"..\\Content\\Dungeon_Tileset\\Png\\DungeonTileset.png");
		Resources::Load<graphics::Texture>(L"SpringFloor", L"..\\Content\\Dungeon_Tileset\\Png\\SpringFloor.bmp");
		Resources::Load<graphics::Texture>(L"Dungeon", L"..\\Content\\Dungeon_Tileset\\Dungeon60.bmp");


		// UI
		// // 플레이어
		Resources::Load<graphics::Texture>(L"HPBAR", L"..\\Content\\RPG_UI\\HUD Health Bar\\HUDHealthBar.png");
		Resources::Load<graphics::Texture>(L"Skill1", L"..\\Content\\RPG_UI\\Skill Icons\\Sorceress Icons\\Sorceress Green Skills\\Png\\Sorceress Green Skill 01.png");
		Resources::Load<graphics::Texture>(L"Skill2", L"..\\Content\\RPG_UI\\Skill Icons\\Warrior Icons\\Warrior Purple Skills\\Png\\Warrior Purple Skill 01.png");
		Resources::Load<graphics::Texture>(L"Skill3", L"..\\Content\\RPG_UI\\Skill Icons\\Necromancer Icons\\Necromancer Green Skills\\Png\\Necromancer Green Skill 02.png");
		Resources::Load<graphics::Texture>(L"Skill4", L"..\\Content\\RPG_UI\\Skill Icons\\Necromancer Icons\\Necromancer Green Skills\\Png\\Necromancer Green Skill 07.png");
		Resources::Load<graphics::Texture>(L"SkillBackground", L"..\\Content\\RPG_UI\\HUD\\Hotbar\\HotbarSkillBackground\\Png\\HotbarSkillBackground2.png");
		Resources::Load<graphics::Texture>(L"SkillNo1", L"..\\Content\\RPG_UI\\HUD\\Hotbar\\HotbarSkillNo\\Png\\HotbarSkillNo1.png");
		Resources::Load<graphics::Texture>(L"SkillNo2", L"..\\Content\\RPG_UI\\HUD\\Hotbar\\HotbarSkillNo\\Png\\HotbarSkillNo2.png");
		Resources::Load<graphics::Texture>(L"SkillNo3", L"..\\Content\\RPG_UI\\HUD\\Hotbar\\HotbarSkillNo\\Png\\HotbarSkillNo3.png");
		Resources::Load<graphics::Texture>(L"SkillNo4", L"..\\Content\\RPG_UI\\HUD\\Hotbar\\HotbarSkillNo\\Png\\HotbarSkillNo4.png");
		Resources::Load<graphics::Texture>(L"HPPotion", L"..\\Content\\Pickups_Pixel\\Pickups\\Potions\\Health\\Png\\SmallHealthPotion.png");
		Resources::Load<graphics::Texture>(L"MPPotion", L"..\\Content\\Pickups_Pixel\\Pickups\\Potions\\Mana\\Png\\SmallManaPotion.png");
		Resources::Load<graphics::Texture>(L"TimeStop", L"..\\Content\\Pickups_Pixel\\Pickups\\Gems\\Png\\PinkGem.png");
		Resources::Load<graphics::Texture>(L"Torch", L"..\\Content\\Lava_Tileset_Pixel\\Animated Tiles\\Lava Dungeon\\Deco\\Png\\Torch.png");
		// // 보스
		Resources::Load<graphics::Texture>(L"BossHP", L"..\\Content\\RPG_UI\\Boss Health Bar\\BossHealthBar.png");
		Resources::Load<graphics::Texture>(L"BossName", L"..\\Content\\RPG_UI\\Boss Names\\Boss Names1.png");
	}
}