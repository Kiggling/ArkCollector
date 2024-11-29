#pragma once

namespace ac::enums
{
	enum class ELayerType
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
		Rigidbody,
		Script,
		Camera,
		End,
	};
	
	enum class EColliderType
	{
		Rect2D,
		Circle2D,
		End,
	};
}