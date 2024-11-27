#pragma once
#include "CommonInclude.h"
#include "acEntity.h"

namespace ac
{
	class Component : public Entity
	{
	public:
		Component(enums::EComponentType InType);
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC InHdc);

		class GameObject* GetOwner() { return mOwner; }
		enums::EComponentType GetType() { return mType; }
		void SetOwner(class GameObject* InOwner) { mOwner = InOwner; }
	private:
		enums::EComponentType mType;
		class GameObject* mOwner;
	};
}
