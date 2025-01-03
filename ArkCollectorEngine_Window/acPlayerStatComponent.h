#pragma once
#include "acStatComponent.h"

namespace ac
{
	class PlayerStatComponent : public StatComponent
	{
	public:
		PlayerStatComponent();
		~PlayerStatComponent();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

		bool GetSkillUsed(int index) { return mbSkillUsed[index]; }
		void SetSkillUsed(int index, bool skillUsed) { mbSkillUsed[index] = skillUsed; }
		float GetSkillCooldown(int index) { return mSkillCooldown[index]; }
		void SetSkillCooldown(int index, float skillCooldown) { mSkillCooldown[index] = skillCooldown; }
		
		bool GetItemUsed(int index) { return mbItemUsed[index]; }
		void SetItemUsed(int index, bool itemUsed) { mbItemUsed[index] = itemUsed; }
		float GetItemCooldown(int index) { return mItemCooldown[index]; }
		void SetItemCooldown(int index, float itemCooldown) { mItemCooldown[index] = itemCooldown; }

	private:
		bool mbSkillUsed[4];
		float mSkillCooldown[4];

		bool mbItemUsed[4];
		float mItemCooldown[4];
	};
}
