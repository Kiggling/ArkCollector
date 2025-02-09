#include "acProjectileScriptComponent.h"
#include "acGameObject.h"
#include "acTransformComponent.h"
#include "acProjectile.h"
#include "acStatComponent.h"
#include "acColliderComponent.h"
#include "acTime.h"
#include "acAnimatorComponent.h"
#include "acPlayerScriptComponent.h"
#include "acBossStatComponent.h"
#include "acBossScriptComponent.h"
#include "acBoss.h"

namespace ac
{
	ProjectileScriptComponent::ProjectileScriptComponent()
		: mDamage(0.0f)
		, mEffectType(eEffectType::Projectile)
		, mDamageType(eDamageType::Projectile)
	{
	}
	ProjectileScriptComponent::~ProjectileScriptComponent()
	{
	}
	void ProjectileScriptComponent::Initialize()
	{
	}
	void ProjectileScriptComponent::Update()
	{
		if (mEffectType == eEffectType::Effect)
		{
			AnimatorComponent* animator = GetOwner()->GetComponent<AnimatorComponent>();

			if (animator->IsComplete())
			{
				GetOwner()->Death();
			}
			return;
		}
		else if (mEffectType == eEffectType::Projectile)
		{
			TransformComponent* tr = GetOwner()->GetComponent<TransformComponent>();
			math::Vector2 pos = tr->GetPosition();
			math::Vector2 startPos = ((Projectile*)GetOwner())->GetStartPosition();
			float range = ((Projectile*)GetOwner())->GetRange();

			if (math::Vector2::Distance(pos, startPos) >= range)
			{
				GetOwner()->Death();
				return;
			}

			pos += ((Projectile*)GetOwner())->GetVelocity() * Time::DeltaTime();

			if (pos.x < TransformComponent::MovementRangeLeftTop.x || pos.x > TransformComponent::MovementRangeRightBottom.x
				|| pos.y < TransformComponent::MovementRangeLeftTop.y || pos.y > TransformComponent::MovementRangeRightBottom.y)
			{
				GetOwner()->Death();
				return;
			}

			tr->SetPosition(pos);
		}
	}
	void ProjectileScriptComponent::LateUpdate()
	{
	}
	void ProjectileScriptComponent::Render(HDC InHdc)
	{
	}
	void ProjectileScriptComponent::OnCollisionEnter(ColliderComponent* other)
	{
		// 1. apply damage to other GameObject
		GameObject* otherGameObj = other->GetOwner();
		PlayerScriptComponent* playerScript = otherGameObj->GetComponent<PlayerScriptComponent>();

		if (playerScript != nullptr && playerScript->GetInvincible())
		{
			return;
		}

		StatComponent* otherStat = otherGameObj->GetComponent<StatComponent>();
		float otherHp = otherStat->GetHp();
		otherStat->SetHp((otherHp - mDamage) < 0.f ? 0.f : otherHp - mDamage);

		Boss* boss = dynamic_cast<Boss*>(otherGameObj);
		if (boss != nullptr)
		{
			BossScriptComponent* bossScript = boss->GetComponent<BossScriptComponent>();

			if (bossScript->GetState() == BossScriptComponent::eState::Gimmick)
			{
				BossStatComponent* bossStat = boss->GetComponent<BossStatComponent>();
				float bossLastHp = bossStat->GetLastHP();
				bossStat->SetLastHP((bossLastHp - mDamage) < 0.f ? 0.f : bossLastHp - mDamage);
			}
		}

		if (mDamageType == eDamageType::Effect)
		{
			return;
		}
		else if (mDamageType == eDamageType::Projectile)
		{
			// TODO: 2. play effect animation


			// 3. destroy projectile
			GetOwner()->Death();
		}
	}
	void ProjectileScriptComponent::OnCollisionStay(ColliderComponent* other)
	{
	}
	void ProjectileScriptComponent::OnCollisionExit(ColliderComponent* other)
	{
	}
}