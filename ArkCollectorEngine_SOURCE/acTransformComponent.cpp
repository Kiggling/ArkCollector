#include "acTransformComponent.h"
#include "acRenderer.h"
#include "acCameraComponent.h"
#include "acApplication.h"

namespace ac
{
	math::Vector2 TransformComponent::MovementRangeLeftTop = math::Vector2(0.f, 0.f);
	math::Vector2 TransformComponent::MovementRangeRightBottom = math::Vector2(0.f, 0.f);

	TransformComponent::TransformComponent()
		: Component(enums::EComponentType::Transform)
		, mPosition(math::Vector2::Zero)
		, mScale(math::Vector2::One)
		, mWidth(0.0f)
		, mHeight(0.0f)
		, mRotation(0.f)
	{
	}
	TransformComponent::~TransformComponent()
	{
	}
	void TransformComponent::Initialize()
	{
	}
	void TransformComponent::Update()
	{
	}
	void TransformComponent::LateUpdate()
	{
	}
	void TransformComponent::Render(HDC InHdc)
	{
	}
}