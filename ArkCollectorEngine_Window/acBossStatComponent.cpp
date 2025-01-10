#include "acBossStatComponent.h"

namespace ac
{
	BossStatComponent::BossStatComponent()
	{
		SetMaxHp(1000.0f);
		SetHp(1000.0f);
		SetDamage(50.0f);
	}
	BossStatComponent::~BossStatComponent()
	{
	}
	void BossStatComponent::Initialize()
	{
	}
	void BossStatComponent::Update()
	{
	}
	void BossStatComponent::LateUpdate()
	{
	}
	void BossStatComponent::Render(HDC InHdc)
	{
	}
}