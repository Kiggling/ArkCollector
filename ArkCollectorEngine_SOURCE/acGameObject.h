#pragma once
#include "CommonInclude.h"
#include "acEntity.h"

namespace ac
{
	class GameObject : public Entity
	{
	public:
		GameObject();
		~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC InHdc);

	private:

	};

}	
