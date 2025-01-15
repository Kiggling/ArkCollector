#include "acBoxCollidier2DComponent.h"
#include "acTransformComponent.h"
#include "acGameObject.h"

namespace ac
{
	BoxCollidier2DComponent::BoxCollidier2DComponent()
		: ColliderComponent(enums::EColliderType::Rect2D)
	{
	}
	BoxCollidier2DComponent::~BoxCollidier2DComponent()
	{
	}
	void BoxCollidier2DComponent::Initialize()
	{
		TransformComponent* tr = this->GetOwner()->GetComponent<TransformComponent>();
		SetCenterPosition(tr->GetPosition());
	}
	void BoxCollidier2DComponent::Update()
	{
		if (!GetActivate())
		{
			return;
		}
	}
	void BoxCollidier2DComponent::LateUpdate()
	{
		if (!GetActivate())
		{
			return;
		}
	}
	void BoxCollidier2DComponent::Render(HDC InHdc)
	{
		if (!GetActivate())
		{
			return;
		}
		TransformComponent* tr = this->GetOwner()->GetComponent<TransformComponent>();
		math::Vector2 centerPos = tr->GetPosition();
		float gameObjWidth = tr->GetWidth();
		float gameObjHeight = tr->GetHeight();

		centerPos.x = centerPos.x + GetOffset().x;
		centerPos.y = centerPos.y + GetOffset().y;

		SetCenterPosition(centerPos);

		//HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		//HBRUSH oldBrush = (HBRUSH)SelectObject(InHdc, transparentBrush);

		//HPEN greenPen = CreatePen(PS_SOLID, 2,RGB(0, 255, 0));
		//HPEN oldPen = (HPEN)SelectObject(InHdc, greenPen);

		//Rectangle(InHdc
		//	, centerPos.x - GetSize().x / 2
		//	, centerPos.y - GetSize().y / 2
		//	, centerPos.x + GetSize().x / 2
		//	, centerPos.y + GetSize().y / 2);

		//SelectObject(InHdc, oldBrush);
		//SelectObject(InHdc, oldPen);
		//DeleteObject(greenPen);
	}
}