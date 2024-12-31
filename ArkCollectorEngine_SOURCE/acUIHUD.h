#pragma once
#include "CommonInclude.h"
#include "acUIBase.h"
#include "acTexture.h"

namespace ac
{
	class UIHUD : public UIBase
	{
	public:
		UIHUD();
		~UIHUD();

		virtual void OnInit();
		virtual void OnActive();
		virtual void OnInActive();
		virtual void OnUpdate();
		virtual void OnLateUpdate();
		virtual void OnRender(HDC InHdc);
		virtual void OnClear();

	private:
		graphics::Texture* mTexture;
	};
}