#include "acTransformComponent.h"

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