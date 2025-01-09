#pragma once
#include "CommonInclude.h"
#include "acComponent.h"

namespace ac
{
	class ColliderComponent : public Component
	{
	public:
		ColliderComponent(enums::EColliderType InType);
		~ColliderComponent();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

		virtual void OnCollisionEnter(ColliderComponent* other);
		virtual void OnCollisionStay(ColliderComponent* other);
		virtual void OnCollisionExit(ColliderComponent* other);

		bool GetActivate() { return mbActivate; }
		math::Vector2 GetSize() { return mSize; }
		math::Vector2 GetOffset() { return mOffset; }
		math::Vector2 GetCenterPosition() { return mCenterPosition; }
		enums::EColliderType GetColliderType() { return mColliderType; }
		UINT GetID() { return mID; }
		void SetActivate(bool InState) { mbActivate = InState; }
		void SetSize(math::Vector2 InSize) { mSize = InSize; }
		void SetOffset(math::Vector2 InOffset) { mOffset = InOffset; }
		void SetCenterPosition(math::Vector2 InCenterPosition) { mCenterPosition = InCenterPosition; }

	private:
		bool mbActivate;
		static UINT32 mCollisionID;
		UINT32 mID;
		enums::EColliderType mColliderType;
		math::Vector2 mCenterPosition;
		math::Vector2 mSize;
		math::Vector2 mOffset;
	};
}