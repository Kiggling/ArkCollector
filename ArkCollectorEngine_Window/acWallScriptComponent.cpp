#include "acWallScriptComponent.h"
#include "acAnimatorComponent.h"
#include "acWall.h"
#include "acTime.h"
#include "acResources.h"

namespace ac
{
	WallScriptComponent::WallScriptComponent()
		: mTime(0.f)
		, mState(eState::Build)
	{
	}
	WallScriptComponent::~WallScriptComponent()
	{
	}
	void WallScriptComponent::Initialize()
	{
	}
	void WallScriptComponent::Update()
	{
		switch (mState)
		{
		case ac::WallScriptComponent::eState::Build:
			build();
			break;
		case ac::WallScriptComponent::eState::Destroy:
			destroy();
			break;
		case ac::WallScriptComponent::eState::End:
			break;
		default:
			break;
		}
	}
	void WallScriptComponent::LateUpdate()
	{
	}
	void WallScriptComponent::Render(HDC InHdc)
	{
	}
	void WallScriptComponent::OnCollisionEnter(ColliderComponent* other)
	{
	}
	void WallScriptComponent::OnCollisionStay(ColliderComponent* other)
	{
	}
	void WallScriptComponent::OnCollisionExit(ColliderComponent* other)
	{
	}
	void WallScriptComponent::build()
	{
		mTime += Time::DeltaTime();
		if (mTime >= 7.f)
		{
			mTime = 0.f;
			Wall* owner = dynamic_cast<Wall*>(GetOwner());
			if (owner == nullptr)
			{
				assert(0);
			}

			AnimatorComponent* wallAnimator = owner->GetComponent<AnimatorComponent>();
			std::wstring animationName = L"WallDestroy";
			animationName += directions[(UINT)owner->GetDirection()];
			graphics::Texture* wallTexture = Resources::Find<graphics::Texture>(animationName);
			wallAnimator->CreateAnimation(animationName, wallTexture, math::Vector2(0.0f, 0.0f), math::Vector2(36.0f, 64.0f), math::Vector2::Zero, 6, 0.2f);
			wallAnimator->PlayAnimation(animationName, false);

			mState = eState::Destroy;
		}
	}
	void WallScriptComponent::destroy()
	{
		AnimatorComponent* wallAnimator = GetOwner()->GetComponent<AnimatorComponent>();
		if (wallAnimator->IsComplete())
		{
			GetOwner()->Death();
		}
	}
}