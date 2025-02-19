﻿#pragma once
#include "..\\ArkCollectorEngine_SOURCE\\acResources.h"
#include "..\\ArkCollectorEngine_SOURCE\\acTexture.h"
#include "..\\ArkCollectorEngine_SOURCE\\acAudioClip.h"


namespace ac
{
	void PlayerResources()
	{
		// Player-Skeleton-Hunter
		// 			Idle,
		//			Walk,
		//			Jump,
		//			Land,
		//			Attack,
		//			Hurt,
		//			Death,
		//			End,
		{
			// Idle
			Resources::Load<graphics::Texture>(L"PlayerIdleDown", L"..\\Content\\Skeleton_Hunter\\Down\\Png\\SkeletonWithBowDownIdle.png");
			Resources::Load<graphics::Texture>(L"PlayerIdleLeft", L"..\\Content\\Skeleton_Hunter\\Left\\Png\\SkeletonWithBowLeftIdle.png");
			Resources::Load<graphics::Texture>(L"PlayerIdleRight", L"..\\Content\\Skeleton_Hunter\\Right\\Png\\SkeletonWithBowRightIdle.png");
			Resources::Load<graphics::Texture>(L"PlayerIdleUp", L"..\\Content\\Skeleton_Hunter\\Up\\Png\\SkeletonWithBowUpIdle.png");
			// Walk
			Resources::Load<graphics::Texture>(L"PlayerWalkDown", L"..\\Content\\Skeleton_Hunter\\Down\\Png\\SkeletonWithBowDownWalk.png");
			Resources::Load<graphics::Texture>(L"PlayerWalkLeft", L"..\\Content\\Skeleton_Hunter\\Left\\Png\\SkeletonWithBowLeftWalk.png");
			Resources::Load<graphics::Texture>(L"PlayerWalkRight", L"..\\Content\\Skeleton_Hunter\\Right\\Png\\SkeletonWithBowRightWalk.png");
			Resources::Load<graphics::Texture>(L"PlayerWalkUp", L"..\\Content\\Skeleton_Hunter\\Up\\Png\\SkeletonWithBowUpWalk.png");
			// Jump
			Resources::Load<graphics::Texture>(L"PlayerJumpDown", L"..\\Content\\Skeleton_Hunter\\Down\\Png\\SkeletonWithBowDownJump.png");
			Resources::Load<graphics::Texture>(L"PlayerJumpLeft", L"..\\Content\\Skeleton_Hunter\\Left\\Png\\SkeletonWithBowLeftJump.png");
			Resources::Load<graphics::Texture>(L"PlayerJumpRight", L"..\\Content\\Skeleton_Hunter\\Right\\Png\\SkeletonWithBowRightJump.png");
			Resources::Load<graphics::Texture>(L"PlayerJumpUp", L"..\\Content\\Skeleton_Hunter\\Up\\Png\\SkeletonWithBowUpJump.png");
			// Land
			Resources::Load<graphics::Texture>(L"PlayerLandDown", L"..\\Content\\Skeleton_Hunter\\Down\\Png\\SkeletonWithBowDownLand.png");
			Resources::Load<graphics::Texture>(L"PlayerLandLeft", L"..\\Content\\Skeleton_Hunter\\Left\\Png\\SkeletonWithBowLeftLand.png");
			Resources::Load<graphics::Texture>(L"PlayerLandRight", L"..\\Content\\Skeleton_Hunter\\Right\\Png\\SkeletonWithBowRightLand.png");
			Resources::Load<graphics::Texture>(L"PlayerLandUp", L"..\\Content\\Skeleton_Hunter\\Up\\Png\\SkeletonWithBowUpLand.png");
			// Attack
			Resources::Load<graphics::Texture>(L"PlayerAttackDown", L"..\\Content\\Skeleton_Hunter\\Down\\Png\\SkeletonWithBowDownAttack01.png");
			Resources::Load<graphics::Texture>(L"PlayerAttackLeft", L"..\\Content\\Skeleton_Hunter\\Left\\Png\\SkeletonWithBowLeftAttack01.png");
			Resources::Load<graphics::Texture>(L"PlayerAttackRight", L"..\\Content\\Skeleton_Hunter\\Right\\Png\\SkeletonWithBowRightAttack01.png");
			Resources::Load<graphics::Texture>(L"PlayerAttackUp", L"..\\Content\\Skeleton_Hunter\\Up\\Png\\SkeletonWithBowUpAttack01.png");
			// Hurt
			Resources::Load<graphics::Texture>(L"PlayerHurtDown", L"..\\Content\\Skeleton_Hunter\\Down\\Png\\SkeletonWithBowDownHurt.png");
			Resources::Load<graphics::Texture>(L"PlayerHurtLeft", L"..\\Content\\Skeleton_Hunter\\Left\\Png\\SkeletonWithBowLeftHurt.png");
			Resources::Load<graphics::Texture>(L"PlayerHurtRight", L"..\\Content\\Skeleton_Hunter\\Right\\Png\\SkeletonWithBowRightHurt.png");
			Resources::Load<graphics::Texture>(L"PlayerHurtUp", L"..\\Content\\Skeleton_Hunter\\Up\\Png\\SkeletonWithBowUpHurt.png");
			// Death
			Resources::Load<graphics::Texture>(L"PlayerDeathDown", L"..\\Content\\Skeleton_Hunter\\Down\\Png\\SkeletonWithBowDownDeath.png");
			Resources::Load<graphics::Texture>(L"PlayerDeathLeft", L"..\\Content\\Skeleton_Hunter\\Left\\Png\\SkeletonWithBowLeftDeath.png");
			Resources::Load<graphics::Texture>(L"PlayerDeathRight", L"..\\Content\\Skeleton_Hunter\\Right\\Png\\SkeletonWithBowRightDeath.png");
			Resources::Load<graphics::Texture>(L"PlayerDeathUp", L"..\\Content\\Skeleton_Hunter\\Up\\Png\\SkeletonWithBowUpDeath.png");
		}

		// Player Skill
		{
			Resources::Load<graphics::Texture>(L"PlayerArrowDown", L"..\\Content\\Skeleton_Hunter\\Projectile\\Arrow\\SkeletonWithBowDownAttackArrow.png");
			Resources::Load<graphics::Texture>(L"PlayerArrowLeft", L"..\\Content\\Skeleton_Hunter\\Projectile\\Arrow\\SkeletonWithBowLeftAttackArrow.png");
			Resources::Load<graphics::Texture>(L"PlayerArrowRight", L"..\\Content\\Skeleton_Hunter\\Projectile\\Arrow\\SkeletonWithBowRightAttackArrow.png");
			Resources::Load<graphics::Texture>(L"PlayerArrowUp", L"..\\Content\\Skeleton_Hunter\\Projectile\\Arrow\\SkeletonWithBowUpAttackArrow.png");

			//Resources::MergePngByFolder(L"..\\Content\\Skeleton_Hunter\\Projectile\\Fireball\\Right", L"..\\Content\\Skeleton_Hunter\\Projectile\\Fireball\\PlayerFireballRight.png");
			//Resources::MergePngByFolder(L"..\\Content\\Skeleton_Hunter\\Projectile\\Fireball\\Left", L"..\\Content\\Skeleton_Hunter\\Projectile\\Fireball\\PlayerFireballLeft.png");
			//Resources::MergePngByFolder(L"..\\Content\\Skeleton_Hunter\\Projectile\\Fireball\\Up", L"..\\Content\\Skeleton_Hunter\\Projectile\\Fireball\\PlayerFireballUp.png");
			//Resources::MergePngByFolder(L"..\\Content\\Skeleton_Hunter\\Projectile\\Fireball\\Down", L"..\\Content\\Skeleton_Hunter\\Projectile\\Fireball\\PlayerFireballDown.png");

			Resources::Load<graphics::Texture>(L"PlayerFireballRight", L"..\\Content\\Skeleton_Hunter\\Projectile\\Fireball\\PlayerFireballRight.png");
			Resources::Load<graphics::Texture>(L"PlayerFireballLeft", L"..\\Content\\Skeleton_Hunter\\Projectile\\Fireball\\PlayerFireballLeft.png");
			Resources::Load<graphics::Texture>(L"PlayerFireballUp", L"..\\Content\\Skeleton_Hunter\\Projectile\\Fireball\\PlayerFireballUp.png");
			Resources::Load<graphics::Texture>(L"PlayerFireballDown", L"..\\Content\\Skeleton_Hunter\\Projectile\\Fireball\\PlayerFireballDown.png");

			Resources::Load<graphics::Texture>(L"PlayerShield", L"..\\Content\\Skeleton_Hunter\\Shield\\PlayerShield.png");

			//Resources::MergePngByFolder(L"..\\Content\\Skeleton_Hunter\\Projectile\\LightningArrow\\Right", L"..\\Content\\Skeleton_Hunter\\Projectile\\LightningArrow\\PlayerLightningArrowRight.png");
			//Resources::MergePngByFolder(L"..\\Content\\Skeleton_Hunter\\Projectile\\LightningArrow\\Left", L"..\\Content\\Skeleton_Hunter\\Projectile\\LightningArrow\\PlayerLightningArrowLeft.png");
			//Resources::MergePngByFolder(L"..\\Content\\Skeleton_Hunter\\Projectile\\LightningArrow\\Up", L"..\\Content\\Skeleton_Hunter\\Projectile\\LightningArrow\\PlayerLightningArrowUp.png");
			//Resources::MergePngByFolder(L"..\\Content\\Skeleton_Hunter\\Projectile\\LightningArrow\\Down", L"..\\Content\\Skeleton_Hunter\\Projectile\\LightningArrow\\PlayerLightningArrowDown.png");

			Resources::Load<graphics::Texture>(L"PlayerLightningArrowRight", L"..\\Content\\Skeleton_Hunter\\Projectile\\LightningArrow\\PlayerLightningArrowRight.png");
			Resources::Load<graphics::Texture>(L"PlayerLightningArrowLeft", L"..\\Content\\Skeleton_Hunter\\Projectile\\LightningArrow\\PlayerLightningArrowLeft.png");
			Resources::Load<graphics::Texture>(L"PlayerLightningArrowUp", L"..\\Content\\Skeleton_Hunter\\Projectile\\LightningArrow\\PlayerLightningArrowUp.png");
			Resources::Load<graphics::Texture>(L"PlayerLightningArrowDown", L"..\\Content\\Skeleton_Hunter\\Projectile\\LightningArrow\\PlayerLightningArrowDown.png");

			//Resources::MergePngByFolder(L"..\\Content\\Skeleton_Hunter\\Projectile\\Blackhole\\Right", L"..\\Content\\Skeleton_Hunter\\Projectile\\Blackhole\\PlayerBlackholeRight.png");
			//Resources::MergePngByFolder(L"..\\Content\\Skeleton_Hunter\\Projectile\\Blackhole\\Left", L"..\\Content\\Skeleton_Hunter\\Projectile\\Blackhole\\PlayerBlackholeLeft.png");
			//Resources::MergePngByFolder(L"..\\Content\\Skeleton_Hunter\\Projectile\\Blackhole\\Up", L"..\\Content\\Skeleton_Hunter\\Projectile\\Blackhole\\PlayerBlackholeUp.png");
			//Resources::MergePngByFolder(L"..\\Content\\Skeleton_Hunter\\Projectile\\Blackhole\\Down", L"..\\Content\\Skeleton_Hunter\\Projectile\\Blackhole\\PlayerBlackholeDown.png");

			Resources::Load<graphics::Texture>(L"PlayerBlackholeRight", L"..\\Content\\Skeleton_Hunter\\Projectile\\Blackhole\\PlayerBlackholeRight.png");
			Resources::Load<graphics::Texture>(L"PlayerBlackholeLeft", L"..\\Content\\Skeleton_Hunter\\Projectile\\Blackhole\\PlayerBlackholeLeft.png");
			Resources::Load<graphics::Texture>(L"PlayerBlackholeUp", L"..\\Content\\Skeleton_Hunter\\Projectile\\Blackhole\\PlayerBlackholeUp.png");
			Resources::Load<graphics::Texture>(L"PlayerBlackholeDown", L"..\\Content\\Skeleton_Hunter\\Projectile\\Blackhole\\PlayerBlackholeDown.png");
		}

		// Player Sound
		{
			// pickup
			Resources::Load<AudioClip>(L"PlayerPickup", L"..\\Content\\Sound\\Player\\Player_Pickup.wav");
			// jump
			Resources::Load<AudioClip>(L"PlayerJump", L"..\\Content\\Sound\\Player\\Player_Jump.wav");
			// hurt
			Resources::Load<AudioClip>(L"PlayerHurt", L"..\\Content\\Sound\\Player\\Player_Hurt.wav");
			// death
			Resources::Load<AudioClip>(L"PlayerDeath", L"..\\Content\\Sound\\Player\\Player_Death.wav");
			// footstep
			Resources::Load<AudioClip>(L"PlayerFootstep", L"..\\Content\\Sound\\Player\\Player_Footstep.wav");
			// base attack
			Resources::Load<AudioClip>(L"PlayerArrowSound", L"..\\Content\\Sound\\Player\\Player_Arrow_Attack.wav");
			// skills
			Resources::Load<AudioClip>(L"PlayerSkill01Sound", L"..\\Content\\Sound\\Player\\Player_Skill01.wav");
			Resources::Load<AudioClip>(L"PlayerSkill02Sound", L"..\\Content\\Sound\\Player\\Player_Skill02.wav");
			Resources::Load<AudioClip>(L"PlayerSkill03Sound", L"..\\Content\\Sound\\Player\\Player_Skill03.wav");
			Resources::Load<AudioClip>(L"PlayerSkill04Sound", L"..\\Content\\Sound\\Player\\Player_Skill04.wav");
			// items
			Resources::Load<AudioClip>(L"PlayerItem01Sound", L"..\\Content\\Sound\\Player\\Player_Item01.wav");
			Resources::Load<AudioClip>(L"PlayerItem02Sound", L"..\\Content\\Sound\\Player\\Player_Item02.wav");
			//Resources::Load<AudioClip>(L"PlayerItem03Sound", L"..\\Content\\Sound\\Player\\Player_Item03.wav");
			//Resources::Load<AudioClip>(L"PlayerItem04Sound", L"..\\Content\\Sound\\Player\\Player_Item04.wav");
		}
	}
	void MapResources()
	{
		// Map
		{
			Resources::Load<graphics::Texture>(L"Dungeon", L"..\\Content\\Dungeon60.bmp");

			// sound
			Resources::Load<AudioClip>(L"DungeonSound", L"..\\Content\\Sound\\Map\\Dungeon.wav");
		}
	}
	void SceneResources()
	{
		// Scene
		Resources::Load<graphics::Texture>(L"DungeonTileset", L"..\\Content\\Dungeon_Tileset\\Png\\DungeonTileset.png");
		Resources::Load<graphics::Texture>(L"SpringFloor", L"..\\Content\\Dungeon_Tileset\\Png\\SpringFloor.bmp");
		Resources::Load<graphics::Texture>(L"Dungeon", L"..\\Content\\Dungeon_Tileset\\Dungeon60.bmp");
		Resources::Load<graphics::Texture>(L"LampOn", L"..\\Content\\Lava_Tileset_Pixel\\Animated Tiles\\Lava Dungeon\\Deco\\Png\\Lava lamp.png");
		Resources::Load<graphics::Texture>(L"LampOff", L"..\\Content\\Lava_Tileset_Pixel\\Animated Tiles\\Lava Dungeon\\Deco\\Png\\Lava lamp off.png");

		Resources::Load<graphics::Texture>(L"Cover_5", L"..\\Content\\Cover\\black_5.png");
		Resources::Load<graphics::Texture>(L"Cover_4", L"..\\Content\\Cover\\black_4.png");
		Resources::Load<graphics::Texture>(L"Cover_3", L"..\\Content\\Cover\\black_3.png");
		Resources::Load<graphics::Texture>(L"Cover_2", L"..\\Content\\Cover\\black_2.png");
		Resources::Load<graphics::Texture>(L"Cover_1", L"..\\Content\\Cover\\black_1.png");
		Resources::Load<graphics::Texture>(L"Cover_0", L"..\\Content\\Cover\\black_0.png");
	}
	void UIResources()
	{
		// UI
		{
			// 플레이어
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

			// 보스
			Resources::Load<graphics::Texture>(L"BossHP", L"..\\Content\\RPG_UI\\Boss Health Bar\\BossHealthBar.png");
			Resources::Load<graphics::Texture>(L"BossName", L"..\\Content\\RPG_UI\\Boss Names\\Boss Names1.png");
		}
	}
	void BossResources()
	{
		// Boss-Skeleton-Boss
		// 			Idle,
		//			Walk,
		//			Jump,
		//			Land,
		//			Attack,
		//			Hurt,
		//			Death,
		//			End,
		{
			// Idle
			Resources::Load<graphics::Texture>(L"BossIdleDown", L"..\\Content\\Skeleton_Boss\\Down\\Png\\AncientSkeletonDownIdle.png");
			Resources::Load<graphics::Texture>(L"BossIdleUp", L"..\\Content\\Skeleton_Boss\\Up\\Png\\AncientSkeletonUpIdle.png");
			Resources::Load<graphics::Texture>(L"BossIdleRight", L"..\\Content\\Skeleton_Boss\\Right\\Png\\AncientSkeletonRightIdle.png");
			Resources::Load<graphics::Texture>(L"BossIdleLeft", L"..\\Content\\Skeleton_Boss\\Left\\Png\\AncientSkeletonLeftIdle.png");
			// Walk
			Resources::Load<graphics::Texture>(L"BossWalkDown", L"..\\Content\\Skeleton_Boss\\Down\\Png\\AncientSkeletonDownWalk.png");
			Resources::Load<graphics::Texture>(L"BossWalkUp", L"..\\Content\\Skeleton_Boss\\Up\\Png\\AncientSkeletonUpWalk.png");
			Resources::Load<graphics::Texture>(L"BossWalkRight", L"..\\Content\\Skeleton_Boss\\Right\\Png\\AncientSkeletonRightWalk.png");
			Resources::Load<graphics::Texture>(L"BossWalkLeft", L"..\\Content\\Skeleton_Boss\\Left\\Png\\AncientSkeletonLeftWalk.png");
			// Jump
			Resources::Load<graphics::Texture>(L"BossJumpDown", L"..\\Content\\Skeleton_Boss\\Down\\Png\\AncientSkeletonDownJump.png");
			Resources::Load<graphics::Texture>(L"BossJumpUp", L"..\\Content\\Skeleton_Boss\\Up\\Png\\AncientSkeletonUpJump.png");
			Resources::Load<graphics::Texture>(L"BossJumpRight", L"..\\Content\\Skeleton_Boss\\Right\\Png\\AncientSkeletonRightJump.png");
			Resources::Load<graphics::Texture>(L"BossJumpLeft", L"..\\Content\\Skeleton_Boss\\Left\\Png\\AncientSkeletonLeftJump.png");
			// Land
			Resources::Load<graphics::Texture>(L"BossLandDown", L"..\\Content\\Skeleton_Boss\\Down\\Png\\AncientSkeletonDownLand.png");
			Resources::Load<graphics::Texture>(L"BossLandUp", L"..\\Content\\Skeleton_Boss\\Up\\Png\\AncientSkeletonUpLand.png");
			Resources::Load<graphics::Texture>(L"BossLandRight", L"..\\Content\\Skeleton_Boss\\Right\\Png\\AncientSkeletonRightLand.png");
			Resources::Load<graphics::Texture>(L"BossLandLeft", L"..\\Content\\Skeleton_Boss\\Left\\Png\\AncientSkeletonLeftLand.png");
			// Attack01
			Resources::Load<graphics::Texture>(L"BossAttack01Down", L"..\\Content\\Skeleton_Boss\\Down\\Png\\AncientSkeletonDownAttack01.png");
			Resources::Load<graphics::Texture>(L"BossAttack01Up", L"..\\Content\\Skeleton_Boss\\Up\\Png\\AncientSkeletonUpAttack01.png");
			Resources::Load<graphics::Texture>(L"BossAttack01Right", L"..\\Content\\Skeleton_Boss\\Right\\Png\\AncientSkeletonRightAttack01.png");
			Resources::Load<graphics::Texture>(L"BossAttack01Left", L"..\\Content\\Skeleton_Boss\\Left\\Png\\AncientSkeletonLeftAttack01.png");
			// Attack02
			Resources::Load<graphics::Texture>(L"BossAttack02Down", L"..\\Content\\Skeleton_Boss\\Down\\Png\\AncientSkeletonDownAttack02.png");
			Resources::Load<graphics::Texture>(L"BossAttack02Up", L"..\\Content\\Skeleton_Boss\\Up\\Png\\AncientSkeletonUpAttack02.png");
			Resources::Load<graphics::Texture>(L"BossAttack02Right", L"..\\Content\\Skeleton_Boss\\Right\\Png\\AncientSkeletonRightAttack02.png");
			Resources::Load<graphics::Texture>(L"BossAttack02Left", L"..\\Content\\Skeleton_Boss\\Left\\Png\\AncientSkeletonLeftAttack02.png");
			// Attack03
			Resources::Load<graphics::Texture>(L"BossAttack03Down", L"..\\Content\\Skeleton_Boss\\Down\\Png\\AncientSkeletonDownAttack03.png");
			Resources::Load<graphics::Texture>(L"BossAttack03Up", L"..\\Content\\Skeleton_Boss\\Up\\Png\\AncientSkeletonUpAttack03.png");
			Resources::Load<graphics::Texture>(L"BossAttack03Right", L"..\\Content\\Skeleton_Boss\\Right\\Png\\AncientSkeletonRightAttack03.png");
			Resources::Load<graphics::Texture>(L"BossAttack03Left", L"..\\Content\\Skeleton_Boss\\Left\\Png\\AncientSkeletonLeftAttack03.png");
			// Hurt
			Resources::Load<graphics::Texture>(L"BossHurtDown", L"..\\Content\\Skeleton_Boss\\Down\\Png\\AncientSkeletonDownHurt.png");
			Resources::Load<graphics::Texture>(L"BossHurtUp", L"..\\Content\\Skeleton_Boss\\Up\\Png\\AncientSkeletonUpHurt.png");
			Resources::Load<graphics::Texture>(L"BossHurtRight", L"..\\Content\\Skeleton_Boss\\Right\\Png\\AncientSkeletonRightHurt.png");
			Resources::Load<graphics::Texture>(L"BossHurtLeft", L"..\\Content\\Skeleton_Boss\\Left\\Png\\AncientSkeletonLeftHurt.png");
			// Death
			Resources::Load<graphics::Texture>(L"BossDeathDown", L"..\\Content\\Skeleton_Boss\\Down\\Png\\AncientSkeletonDownDeath.png");
			Resources::Load<graphics::Texture>(L"BossDeathUp", L"..\\Content\\Skeleton_Boss\\Up\\Png\\AncientSkeletonUpDeath.png");
			Resources::Load<graphics::Texture>(L"BossDeathRight", L"..\\Content\\Skeleton_Boss\\Right\\Png\\AncientSkeletonRightDeath.png");
			Resources::Load<graphics::Texture>(L"BossDeathLeft", L"..\\Content\\Skeleton_Boss\\Left\\Png\\AncientSkeletonLeftDeath.png");
		}


		// Boss Effects
		{
			// Dust
			Resources::Load<graphics::Texture>(L"Dust", L"..\\Content\\Effects\\Effects\\VFX\\Destroy Effect.png");
			// Wave
			// // Small
			Resources::Load<graphics::Texture>(L"WaveSmallDown", L"..\\Content\\Effects\\Effects\\Wave\\Small\\Down\\WaveSmallDown.png");
			Resources::Load<graphics::Texture>(L"WaveSmallUp", L"..\\Content\\Effects\\Effects\\Wave\\Small\\Up\\WaveSmallUp.png");
			Resources::Load<graphics::Texture>(L"WaveSmallRight", L"..\\Content\\Effects\\Effects\\Wave\\Small\\Right\\WaveSmallRight.png");
			Resources::Load<graphics::Texture>(L"WaveSmallLeft", L"..\\Content\\Effects\\Effects\\Wave\\Small\\Left\\WaveSmallLeft.png");
			// // Big
			Resources::Load<graphics::Texture>(L"WaveBigDown", L"..\\Content\\Effects\\Effects\\Wave\\Big\\Down\\WaveBigDown.png");
			Resources::Load<graphics::Texture>(L"WaveBigUp", L"..\\Content\\Effects\\Effects\\Wave\\Big\\Up\\WaveBigUp.png");
			Resources::Load<graphics::Texture>(L"WaveBigRight", L"..\\Content\\Effects\\Effects\\Wave\\Big\\Right\\WaveBigRight.png");
			Resources::Load<graphics::Texture>(L"WaveBigLeft", L"..\\Content\\Effects\\Effects\\Wave\\Big\\Left\\WaveBigLeft.png");
			// Rain
			// // Small
			Resources::Load<graphics::Texture>(L"RainSmallOrange", L"..\\Content\\Effects\\Effects\\Pickup effects\\Png\\Gem Pickup effect.png");
			Resources::Load<graphics::Texture>(L"RainSmallYello", L"..\\Content\\Effects\\Effects\\Pickup effects\\Png\\Gold Pickup effect.png");
			Resources::Load<graphics::Texture>(L"RainSmallRed", L"..\\Content\\Effects\\Effects\\Pickup effects\\Png\\Health Potion Pickup effect.png");
			Resources::Load<graphics::Texture>(L"RainSmallBlue", L"..\\Content\\Effects\\Effects\\Pickup effects\\Png\\Mana Potion Pickup effect.png");
			Resources::Load<graphics::Texture>(L"RainSmallGreen", L"..\\Content\\Effects\\Effects\\Pickup effects\\Png\\Stamina Potion Pickup effect.png");
			// // Big
			Resources::Load<graphics::Texture>(L"RainBigOrange", L"..\\Content\\Effects\\Effects\\Rarity Effects\\Png\\Legendary effect.png");
			Resources::Load<graphics::Texture>(L"RainBigYello", L"..\\Content\\Effects\\Effects\\Rarity Effects\\Png\\Rare effect.png");
			Resources::Load<graphics::Texture>(L"RainBigRed", L"..\\Content\\Effects\\Effects\\Rarity Effects\\Png\\Mythic effect.png");
			Resources::Load<graphics::Texture>(L"RainBigBlue", L"..\\Content\\Effects\\Effects\\Rarity Effects\\Png\\Magic effect.png");
			Resources::Load<graphics::Texture>(L"RainBigGray", L"..\\Content\\Effects\\Effects\\Rarity Effects\\Png\\Common effect.png");
			// Fire
			Resources::Load<graphics::Texture>(L"FireEruption", L"..\\Content\\Effects\\Effects\\Fire\\FireEruption.png");
		}
	}
	void WallResources()
	{
		// Wall
		{
			Resources::Load<graphics::Texture>(L"WallBuildDown", L"..\\Content\\craftpix-free-magic-and-traps-top-down-pixel-art-asset\\2 Barricades\\Down\\Build.png");
			Resources::Load<graphics::Texture>(L"WallBuildUp", L"..\\Content\\craftpix-free-magic-and-traps-top-down-pixel-art-asset\\2 Barricades\\Up\\Build.png");
			Resources::Load<graphics::Texture>(L"WallBuildRight", L"..\\Content\\craftpix-free-magic-and-traps-top-down-pixel-art-asset\\2 Barricades\\Right\\Build.png");
			Resources::Load<graphics::Texture>(L"WallBuildLeft", L"..\\Content\\craftpix-free-magic-and-traps-top-down-pixel-art-asset\\2 Barricades\\Left\\Build.png");

			Resources::Load<graphics::Texture>(L"WallDestroyDown", L"..\\Content\\craftpix-free-magic-and-traps-top-down-pixel-art-asset\\2 Barricades\\Down\\Destroy.png");
			Resources::Load<graphics::Texture>(L"WallDestroyUp", L"..\\Content\\craftpix-free-magic-and-traps-top-down-pixel-art-asset\\2 Barricades\\Up\\Destroy.png");
			Resources::Load<graphics::Texture>(L"WallDestroyRight", L"..\\Content\\craftpix-free-magic-and-traps-top-down-pixel-art-asset\\2 Barricades\\Right\\Destroy.png");
			Resources::Load<graphics::Texture>(L"WallDestroyLeft", L"..\\Content\\craftpix-free-magic-and-traps-top-down-pixel-art-asset\\2 Barricades\\Left\\Destroy.png");
		}
	}
	void LampResources()
	{
		// Lamp
		{
			// texture
			Resources::Load<graphics::Texture>(L"LampOn", L"..\\Content\\Lava_Tileset_Pixel\\Animated Tiles\\Lava Dungeon\\Deco\\Png\\Lava lamp.png");
			Resources::Load<graphics::Texture>(L"LampOff", L"..\\Content\\Lava_Tileset_Pixel\\Animated Tiles\\Lava Dungeon\\Deco\\Png\\Lava lamp off.png");

			// sound
			Resources::Load<AudioClip>(L"LampOnSound", L"..\\Content\\Sound\\Lamp\\Lamp_On.wav");
			Resources::Load<AudioClip>(L"LampOffSound", L"..\\Content\\Sound\\Lamp\\Lamp_Off.wav");
		}
	}
	void LoadResources()
	{
		//Resources::Load<graphics::Texture>();
		std::thread t1(PlayerResources);
		std::thread t2(BossResources);
		std::thread t3(LampResources);
		std::thread t4(MapResources);
		std::thread t5(SceneResources);
		std::thread t6(UIResources);
		std::thread t7(WallResources);

		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();
		t6.join();
		t7.join();
	}
}