#pragma once
#include "..\\ArkCollectorEngine_SOURCE\\acResources.h"
#include "..\\ArkCollectorEngine_SOURCE\\acTexture.h"
#include "..\\ArkCollectorEngine_SOURCE\\acAudioClip.h"

namespace ac
{
	void LoadResources()
	{
		//Resources::Load<graphics::Texture>();

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
			// death
			Resources::Load<AudioClip>(L"PlayerDeath", L"..\\Content\\Sound\\Player\\Player_Death.wav");
			// footstep
			Resources::Load<AudioClip>(L"Playerfootstep0", L"..\\Content\\Sound\\Player\\Player_Footstep0.wav");
			Resources::Load<AudioClip>(L"Playerfootstep1", L"..\\Content\\Sound\\Player\\Player_Footstep1.wav");
			// base attack
			Resources::Load<AudioClip>(L"PlayerArrowSound", L"..\\Content\\Sound\\Player\\Player_Arrow_Attack.wav");
			// skills
			Resources::Load<AudioClip>(L"PlayerSkill01Sound", L"..\\Content\\Sound\\Player\\Player_Skill01.wav");
			Resources::Load<AudioClip>(L"PlayerSkill02Sound", L"..\\Content\\Sound\\Player\\Player_Skill02.wav");
			//Resources::Load<AudioClip>(L"PlayerSkill03Sound", L"..\\Content\\Sound\\Player\\Player_Skill03.wav");
			//Resources::Load<AudioClip>(L"PlayerSkill04Sound", L"..\\Content\\Sound\\Player\\Player_Skill04.wav");
		}
		
		// Map
		{
			Resources::Load<graphics::Texture>(L"Dungeon", L"..\\Content\\Dungeon60.bmp");
		}

		// Scene
		Resources::Load<graphics::Texture>(L"DungeonTileset", L"..\\Content\\Dungeon_Tileset\\Png\\DungeonTileset.png");
		Resources::Load<graphics::Texture>(L"SpringFloor", L"..\\Content\\Dungeon_Tileset\\Png\\SpringFloor.bmp");
		Resources::Load<graphics::Texture>(L"Dungeon", L"..\\Content\\Dungeon_Tileset\\Dungeon60.bmp");


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

	}
}