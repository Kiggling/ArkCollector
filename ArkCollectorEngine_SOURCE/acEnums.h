#pragma once

namespace ac::enums
{
	enum class eLayerType
	{
		None,
		BackGround,
		Tile,
		Player,
		Floor,
		Particle,
		Max = 16,
	};
  
	enum class EComponentType
	{
		Transform,
		Collider,
		Script,
		SpriteRenderer,
		Animator,
		End,
	};

	enum class eResourceType
	{
		Texture,
		AudioClip,
		Animation,
		Prefab,
		End,
	};
}