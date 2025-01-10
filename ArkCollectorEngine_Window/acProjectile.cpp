#include "acProjectile.h"

namespace ac
{
	Projectile::Projectile()
		: mVelocity(math::Vector2::Zero)
		, mRange(500.0f)
		, mStartPosition(math::Vector2::Zero)
	{
	}
	Projectile::Projectile(math::Vector2 velocity)
		: mRange(500.0f)
		, mStartPosition(math::Vector2::Zero)
	{
		mVelocity = velocity;
	}
	Projectile::~Projectile()
	{
		int a = 0;
	}
	void Projectile::Initialize()
	{
		GameObject::Initialize();
	}
	void Projectile::Update()
	{
		GameObject::Update();
	}
	void Projectile::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Projectile::Render(HDC InHdc)
	{
		GameObject::Render(InHdc);
	}
}