#include "acTransformComponent.h"
#include "acRenderer.h"
#include "acCameraComponent.h"

namespace ac
{
	TransformComponent::TransformComponent()
		: Component(enums::EComponentType::Transform)
		, mPosition(math::Vector2::Zero)
		, mRotation(math::Vector2::Zero)
		, mWidth(0.0f)
		, mHeight(0.0f)
		, mScale(1.f)

	{
	}
	TransformComponent::~TransformComponent()
	{
	}
	void TransformComponent::Initialize()
	{
		if (renderer::mainCamera == nullptr)
		{
			return;
		}
		mPosition = renderer::mainCamera->GetPositionInCameraSpace(mPosition);
	}
	void TransformComponent::Update()
	{
		if (renderer::mainCamera == nullptr)
		{
			return;
		}
		mPosition = renderer::mainCamera->GetPositionInCameraSpace(mPosition);
	}
	void TransformComponent::LateUpdate()
	{
	}
	void TransformComponent::Render(HDC InHdc)
	{
	}
}