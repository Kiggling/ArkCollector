#include "acCircleCollider2DComponent.h"
#include "acTransformComponent.h"
#include "acGameObject.h"

namespace ac
{
	CircleCollider2DComponent::CircleCollider2DComponent()
		: ColliderComponent(enums::EColliderType::Circle2D)
	{
	}
	CircleCollider2DComponent::~CircleCollider2DComponent()
	{
	}
	void CircleCollider2DComponent::Initialize()
	{
		TransformComponent* tr = this->GetOwner()->GetCompenet<TransformComponent>();

		SetCenterPosition(tr->GetPosition());
	}
	void CircleCollider2DComponent::Update()
	{
	}
	void CircleCollider2DComponent::LateUpdate()
	{
	}
	void CircleCollider2DComponent::Render(HDC InHdc)
	{
		TransformComponent* tr = this->GetOwner()->GetCompenet<TransformComponent>();
		math::Vector2 centerPos = tr->GetPosition();
		float gameObjWidth = tr->GetWidth();
		float gameObjHeight = tr->GetHeight();

		centerPos.x = centerPos.x + gameObjWidth / 2 + GetOffset().x;
		centerPos.y = centerPos.y + gameObjHeight / 2 + GetOffset().y;

		SetCenterPosition(centerPos);

		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(InHdc, transparentBrush);

		HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		HPEN oldPen = (HPEN)SelectObject(InHdc, greenPen);

		Ellipse(InHdc
			, centerPos.x - GetSize().x / 2
			, centerPos.y - GetSize().y / 2
			, centerPos.x + GetSize().x / 2
			, centerPos.y + GetSize().y / 2);

		SelectObject(InHdc, oldBrush);
		SelectObject(InHdc, oldPen);
		DeleteObject(greenPen);
	}
}