#include "acCameraScriptComponent.h"
#include "acTransformComponent.h"
#include "acGameObject.h"
#include "acInput.h"
#include "acColliderComponent.h"
#include "acTime.h"

namespace ac
{
	CameraScriptComponent::CameraScriptComponent()
	{
	}
	CameraScriptComponent::~CameraScriptComponent()
	{
	}
	void CameraScriptComponent::Initialize()
	{
	}
	void CameraScriptComponent::Update()
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
	void CameraScriptComponent::LateUpdate()
	{
	}
	void CameraScriptComponent::Render(HDC InHdc)
	{
	}
}