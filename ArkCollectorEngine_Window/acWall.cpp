#include "acWall.h"

namespace ac
{
	Wall::Wall()
		: mDirection(eDirection::None)
	{
	}
	Wall::~Wall()
	{
	}
	void Wall::Initialize()
	{
		GameObject::Initialize();
	}
	void Wall::Update()
	{
		GameObject::Update();
	}
	void Wall::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Wall::Render(HDC InHdc)
	{
		GameObject::Render(InHdc);
	}
}