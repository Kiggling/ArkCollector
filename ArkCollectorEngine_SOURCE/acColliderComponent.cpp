#include "acColliderComponent.h"
#include "acScriptComponent.h"
#include "acGameObject.h"

namespace ac
{
	UINT32 ColliderComponent::mCollisionID = 1;

	ColliderComponent::ColliderComponent(enums::EColliderType InType)
		: Component(enums::EComponentType::Collider)
		, mID(mCollisionID++)
		, mColliderType(InType)
		, mSize(math::Vector2::One)
		, mOffset(math::Vector2::Zero)
	{
	}
	ColliderComponent::~ColliderComponent()
	{
	}
	void ColliderComponent::Initialize()
	{
	}
	void ColliderComponent::Update()
	{
	}
	void ColliderComponent::LateUpdate()
	{
	}
	void ColliderComponent::Render(HDC InHdc)
	{
	}
	void ColliderComponent::OnCollisionEnter(ColliderComponent* other)
	{
		ScriptComponent* script = this->GetOwner()->GetCompenet<ScriptComponent>();

		if (script != nullptr)
		{
			script->OnCollisionEnter(other);
		}
		else
		{
			return;
		}
	}
	void ColliderComponent::OnCollisionStay(ColliderComponent* other)
	{
		ScriptComponent* script = this->GetOwner()->GetCompenet<ScriptComponent>();
		if (script != nullptr) 
		{
			script->OnCollisionStay(other);
		}
		else
		{
			return;
		}
	}
	void ColliderComponent::OnCollisionExit(ColliderComponent* other)
	{
		ScriptComponent* script = this->GetOwner()->GetCompenet<ScriptComponent>();
		if (script != nullptr)
		{
			script->OnCollisionExit(other);
		}
		else
		{
			return;
		}
	}
}