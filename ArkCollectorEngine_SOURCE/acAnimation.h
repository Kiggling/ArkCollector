#pragma once
#include "acResource.h"
#include "acTexture.h"

namespace ac
{
	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			math::Vector2 leftTop;
			math::Vector2 size;
			math::Vector2 offset;
			float duration;

			Sprite()
				: leftTop(math::Vector2::Zero)
				, size(math::Vector2::Zero)
				, offset(math::Vector2::Zero)
				, duration(0.0f)
			{

			}
		};

		Animation();
		~Animation();

		HRESULT Load(const std::wstring& path) override;

		void Update();
		void Render(HDC hdc);

		void CreateAnimation(const std::wstring& name
			, graphics::Texture* spriteSheet
			, math::Vector2 leftTop
			, math::Vector2 size
			, math::Vector2 offset
			, UINT spriteLength
			, float duration);

		void Reset();

		bool IsComplete() { return mbComplete; }
		void SetAnimator(class AnimatorComponent* animator) { mAnimator = animator; }
		int GetAnimationSheetIndex() { return mIndex; }

	private:
		class AnimatorComponent* mAnimator;
		graphics::Texture* mTexture;

		std::vector<Sprite> mAnimationSheet;
		int mIndex;
		float mTime;
		bool mbComplete;
	};
}
