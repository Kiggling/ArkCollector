#include "acAnimatorComponent.h"
#include "acResources.h"

namespace ac
{
	AnimatorComponent::AnimatorComponent()
		: Component(enums::EComponentType::Animator)
		, mAnimations{}
		, mActiveAnimation(nullptr)
		, mbLoop(false)
	{
	}
	AnimatorComponent::~AnimatorComponent()
	{
		for (auto& iter : mAnimations)
		{
			delete iter.second;
			iter.second = nullptr;
		}

		for (auto& iter : mEvents)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
	void AnimatorComponent::Initialize()
	{
	}
	void AnimatorComponent::Update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Update();

			Events* events = FindEvents(mActiveAnimation->GetName());

			if (mActiveAnimation->IsComplete() == true)
			{
				if (events)
				{
					events->completeEvent();

					if (mbLoop == true)
						mActiveAnimation->Reset();
				}
			}
		}
	}
	void AnimatorComponent::LateUpdate()
	{
	}
	void AnimatorComponent::Render(HDC hdc)
	{
		if (mActiveAnimation)
			mActiveAnimation->Render(hdc);
	}
	void AnimatorComponent::CreateAnimation(const std::wstring& name
		, graphics::Texture* spriteSheet
		, math::Vector2 leftTop
		, math::Vector2 size
		, math::Vector2 offset
		, UINT spriteLegth
		, float duration)
	{
		Animation* animation = nullptr;
		animation = FindAnimation(name);
		if (animation != nullptr)
			return;

		animation = new Animation();
		animation->SetName(name);
		animation->CreateAnimation(name, spriteSheet
			, leftTop, size, offset, spriteLegth, duration);

		animation->SetAnimator(this);

		Events* events = new Events();
		mEvents.insert(std::make_pair(name, events));

		mAnimations.insert(std::make_pair(name, animation));
	}
	void AnimatorComponent::CreateAnimationByFolder(const std::wstring& name, const std::wstring& path, math::Vector2 offset, float duration)
	{
		Animation* animation = nullptr;
		animation = FindAnimation(name);
		if (animation != nullptr)
			return;

		int fileCount = 0;
		std::filesystem::path fs(path);
		std::vector<graphics::Texture*> images = {};
		for (auto& p : std::filesystem::recursive_directory_iterator(fs))
		{
			std::wstring fileName = p.path().filename();
			std::wstring fullName = p.path();

			graphics::Texture* texture = Resources::Load<graphics::Texture>(fileName, fullName);
			images.push_back(texture);
			fileCount++;
		}

		UINT sheetWidth = images[0]->GetWidth() * fileCount;
		UINT sheetHeight = images[0]->GetHeight();
		graphics::Texture* spriteSheet = graphics::Texture::Create(name, sheetWidth, sheetHeight);

		UINT imageWidth = images[0]->GetWidth();
		UINT imageHeight = images[0]->GetHeight();
		for (size_t i = 0; i < images.size(); i++)
		{
			BitBlt(spriteSheet->GetHdc(), i * imageWidth, 0
				, imageWidth, imageHeight
				, images[i]->GetHdc(), 0, 0, SRCCOPY);
		}

		CreateAnimation(name, spriteSheet, math::Vector2(0.0f, 0.0f), math::Vector2(imageWidth, imageHeight), offset, fileCount, duration);
	}
	Animation* AnimatorComponent::FindAnimation(const std::wstring& name)
	{
		auto iter = mAnimations.find(name);
		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}
	void AnimatorComponent::PlayAnimation(const std::wstring& name, bool loop)
	{
		Animation* animation = FindAnimation(name);
		if (animation == nullptr)
			return;


		if (mActiveAnimation)
		{
			Events* currentEvents
				= FindEvents(mActiveAnimation->GetName());

			if (currentEvents)
				currentEvents->endEvent();
		}


		Events* nextEvents
			= FindEvents(animation->GetName());

		if (nextEvents)
			nextEvents->startEvent();

		mActiveAnimation = animation;
		mActiveAnimation->Reset();
		mbLoop = loop;
	}
	AnimatorComponent::Events* AnimatorComponent::FindEvents(const std::wstring& name)
	{
		auto iter = mEvents.find(name);
		if (iter == mEvents.end())
			return nullptr;

		return iter->second;
	}
	std::function<void()>& AnimatorComponent::GetStartEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);
		return events->startEvent.mEvent;
	}
	std::function<void()>& AnimatorComponent::GetCompleteEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);
		return events->completeEvent.mEvent;
	}
	std::function<void()>& AnimatorComponent::GetEndEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);
		return events->endEvent.mEvent;
	}
}