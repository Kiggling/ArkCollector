#pragma once
#include "CommonInclude.h"

namespace ac
{
	class UIBase
	{
	public:
		UIBase(enums::EUIType InType);
		~UIBase();

		void Initialize();
		void Active();
		void InActive();
		void Update();
		void LateUpdate();
		void Render(HDC InHdc);
		void UIClear();

		virtual void OnInit();
		virtual void OnActive();
		virtual void OnInActive();
		virtual void OnUpdate();
		virtual void OnLateUpdate();
		virtual void OnRender(HDC InHdc);
		virtual void OnClear();

		enums::EUIType GetType() { return mType; }
		void SetFullScreen(bool enable) { mbFullScreen = enable; }
		bool IsFullScreen() { return mbFullScreen; }
		
	private:
		enums::EUIType mType;
		bool mbFullScreen;
		bool mbEnabled;
	};
}