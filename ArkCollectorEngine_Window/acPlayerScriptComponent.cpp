#include "acPlayerScriptComponent.h"
#include "acTransformComponent.h"
#include "acGameObject.h"
#include "acInput.h"
#include "acColliderComponent.h"
#include "acTime.h"

namespace ac
{
	PlayerScriptComponent::PlayerScriptComponent()
	{
	}
	PlayerScriptComponent::~PlayerScriptComponent()
	{
	}
	void PlayerScriptComponent::Initialize()
	{
	}
	void PlayerScriptComponent::Update()
	{
		TransformComponent* tr = this->GetOwner()->GetComponent<TransformComponent>();
		math::Vector2 pos = tr->GetPosition();

		float value = 100.f;

		if (Input::GetKey(EKeyCode::UP))
		{
			pos.y -= value * Time::DeltaTime();
		}
		if (Input::GetKey(EKeyCode::DOWN))
		{
			pos.y += value * Time::DeltaTime();
		}
		if (Input::GetKey(EKeyCode::LEFT))
		{
			pos.x -= value * Time::DeltaTime();
		}
		if (Input::GetKey(EKeyCode::RIGHT))
		{
			pos.x += value * Time::DeltaTime();
		}

		tr->SetPosition(pos);
	}
	void PlayerScriptComponent::LateUpdate()
	{
	}
	void PlayerScriptComponent::Render(HDC InHdc)
	{
	}
	void PlayerScriptComponent::OnCollisionEnter(ColliderComponent* other)
	{
		TransformComponent* tr = other->GetOwner()->GetComponent<TransformComponent>();

		math::Vector2 pos = tr->GetPosition();

		pos.x += 50;
		tr->SetPosition(pos);
	}
	void PlayerScriptComponent::OnCollisionStay(ColliderComponent* other)
	{
	}
	void PlayerScriptComponent::OnCollisionExit(ColliderComponent* other)
	{
	}
}