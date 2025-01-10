#pragma once

namespace ac::enums
{
	enum class ELayerType
	{
		None,
		BackGround,
		Tile,
		Boss,
		Player,
		Floor,
		Particle,
		Max = 16,
	};
  
	enum class EComponentType
	{
		Transform,
		Collider,
		Rigidbody,
		Script,
		SpriteRenderer,
		Animator,
		Camera,
		AudioListener,
		AudioSource,
		Stat,
		End,
	};

	enum class EResourceType
	{
		Texture,
		AudioClip,
		Animation,
		Prefab,
		End,
	};
	
	enum class EColliderType
	{
		Rect2D,
		Circle2D,
		End,
	};

	enum class EUIType
	{
		HUD,
		End,
	};
}