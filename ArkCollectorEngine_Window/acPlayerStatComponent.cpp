#include "acPlayerStatComponent.h"

namespace ac
{
	PlayerStatComponent::PlayerStatComponent()
	{
		SetMaxHp(100.0f);
		SetMaxMp(100.0f);

		SetHp(30.0f);
		SetMp(70.0f);

		SetDamage(50.0f);
		SetAttackSpeed(1.0f);

		float skillCooldown[] = { 2.0f, 3.0f, 5.0f, 10.0f };
		float itemCooldown[] = { 3.0f, 3.0f, 60.0f, 30.0f };

		for (int i = 0; i < 4; i++)
		{
			mbSkillUsed[i] = false;
			mSkillCooldown[i] = skillCooldown[i];

			mbItemUsed[i] = false;
			mItemCooldown[i] = itemCooldown[i];
		}
	}
	PlayerStatComponent::~PlayerStatComponent()
	{
	}
	void PlayerStatComponent::Initialize()
	{
	}
	void PlayerStatComponent::Update()
	{
	}
	void PlayerStatComponent::LateUpdate()
	{
	}
	void PlayerStatComponent::Render(HDC InHdc)
	{
	}
}