#pragma once
#include "CommonInclude.h"
#include "acEntity.h"

namespace ac
{
	class Layer : public Entity
	{
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);
		


	private:
		// ���ӿ�����Ʈ�� ���� vector
	};
}
