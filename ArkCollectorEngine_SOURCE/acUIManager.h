#pragma once
#include "CommonInclude.h"
#include "acUIBase.h"

namespace ac
{
	class UIManager
	{
	public:
		static void OnLoad(enums::EUIType InType);
		static void OnComplete(UIBase* addUI);
		static void OnFail();
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC InHdc);
		static void Push(enums::EUIType InType);
		static void Pop(enums::EUIType InType);
		static void Release();

	private:
		static std::unordered_map<enums::EUIType, UIBase*> mUIs;
		static std::stack<UIBase*> mUIBases;
		static std::queue<enums::EUIType> mRequestUIQueue;
		
	};
}