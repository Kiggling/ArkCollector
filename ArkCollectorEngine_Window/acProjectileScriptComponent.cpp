#include "acProjectileScriptComponent.h"
#include "acGameObject.h"
#include "acTransformComponent.h"
#include "acProjectile.h"
#include "acStatComponent.h"
#include "acColliderComponent.h"

namespace ac
{
	ProjectileScriptComponent::ProjectileScriptComponent()
		: mDamage(0.0f)
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
		TransformComponent* tr = GetOwner()->GetComponent<TransformComponent>();
		math::Vector2 pos = tr->GetPosition();
		math::Vector2 startPos = ((Projectile*)GetOwner())->GetStartPosition();
		float range = ((Projectile*)GetOwner())->GetRange();

		if (math::Vector2::Distance(pos, startPos) >= range)
		{
			GetOwner()->Death();
			return;
		}

		pos += ((Projectile*)GetOwner())->GetVelocity();

		tr->SetPosition(pos);
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
		StatComponent* otherStat = otherGameObj->GetComponent<StatComponent>();
		float otherHp = otherStat->GetHp();
		otherStat->SetHp(otherHp - mDamage);

		// TODO: 2. play effect animation


		// 3. destroy projectile
		GetOwner()->Death();
	}
	void ProjectileScriptComponent::OnCollisionStay(ColliderComponent* other)
	{
	}
	void ProjectileScriptComponent::OnCollisionExit(ColliderComponent* other)
	{
	}
}