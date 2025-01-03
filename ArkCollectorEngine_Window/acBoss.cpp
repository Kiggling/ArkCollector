#include "acBoss.h"


namespace ac
{
	Boss::Boss()
	{
	}
	Boss::~Boss()
	{
	}
	void Boss::Initialize()
	{
		GameObject::Initialize();
	}
	void Boss::Update()
	{
		GameObject::Update();
	}
	void Boss::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Boss::Render(HDC InHdc)
	{
		GameObject::Render(InHdc);
	}
}