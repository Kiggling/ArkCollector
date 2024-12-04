#include "acCameraComponent.h"
#include "acTransformComponent.h"
#include "acGameObject.h"
#include "acApplication.h"

extern ac::Application application;

namespace ac
{
	CameraComponent::CameraComponent()
		: Component(enums::EComponentType::Camera)
		, mCameraPosition(math::Vector2::Zero)
		, mResolution(math::Vector2(1600.0f, 900.0f))
		, mTarget(nullptr)
	{
	}
	CameraComponent::~CameraComponent()
	{

	}
	void CameraComponent::Initialize()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
	}
	void CameraComponent::Update()
	{
		TransformComponent* tr = nullptr;
		if (mTarget == nullptr)
		{
			tr = this->GetOwner()->GetComponent<TransformComponent>();
		}
		else
		{
			tr = mTarget->GetComponent<TransformComponent>();
		}
		mCameraPosition = tr->GetPosition();;
	}
	void CameraComponent::LateUpdate()
	{
	}
	void CameraComponent::Render(HDC InHdc)
	{
	}
	math::Vector2 CameraComponent::GetPositionInCameraSpace(math::Vector2 InPos)
	{
		InPos -= mCameraPosition;
		InPos += mResolution / 2;
		return InPos;
	}
	math::Vector2 CameraComponent::GetPositionInToolScene(math::Vector2 InPos)
	{
		InPos += mCameraPosition;
		InPos -= mResolution / 2;
		return InPos;
	}
}