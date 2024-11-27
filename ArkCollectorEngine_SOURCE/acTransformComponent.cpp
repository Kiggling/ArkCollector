#include "acTransformComponent.h"

namespace ac
{
	TransformComponent::TransformComponent()
		: Component(enums::EComponentType::Transform)
		, mPosition(math::Vector2::Zero)
		, mRotation(math::Vector2::Zero)
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