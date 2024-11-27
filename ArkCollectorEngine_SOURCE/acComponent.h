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
			
		enums::EComponentType GetType() { return mType; }
	private:
		enums::EComponentType mType;
	};
}
