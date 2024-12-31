#include "acUIManager.h"
#include "acUIHUD.h"

namespace ac
{
	std::unordered_map<enums::EUIType, UIBase*> UIManager::mUIs = {};
	std::stack<UIBase*> UIManager::mUIBases = {};
	std::queue<enums::EUIType> UIManager::mRequestUIQueue = {};

	void UIManager::Initialize()
	{
		UIHUD* hud = new UIHUD();
		mUIs.insert({ enums::EUIType::HUD, hud });

	}
	void UIManager::OnLoad(enums::EUIType InType)
	{
		std::unordered_map<enums::EUIType, UIBase*>::iterator iter = mUIs.find(InType);

		if (iter == mUIs.end())
		{
			OnFail();
			return;
		}

		OnComplete(iter->second);
	}
	void UIManager::OnComplete(UIBase* addUI)
	{
		if (addUI == nullptr)
		{
			return;
		}

		addUI->Initialize();
		addUI->Active();
		addUI->Update();

		if (addUI->IsFullScreen())
		{
			std::stack<UIBase*> uiBases = mUIBases;
			while (!uiBases.empty())
			{
				UIBase* uiBase = uiBases.top();
				uiBases.pop();
				if (uiBase)
				{
					uiBase->InActive();
				}
			}
		}

		mUIBases.push(addUI);
	}
	void UIManager::OnFail()
	{
	}
	void UIManager::Update()
	{
		std::stack<UIBase*> uiBases = mUIBases;
		while (!uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();
			if (uiBase)
			{
				uiBase->Update();
				uiBases.pop();
			}
		}

		if (!mRequestUIQueue.empty())
		{
			enums::EUIType requestUI = mRequestUIQueue.front();
			mRequestUIQueue.pop();
			OnLoad(requestUI);
		}
	}
	void UIManager::LateUpdate()
	{
		std::stack<UIBase*> uiBases = mUIBases;
		while (!uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();
			if (uiBase)
			{
				uiBase->LateUpdate();
				uiBases.pop();
			}
		}
	}
	void UIManager::Render(HDC InHdc)
	{
		std::stack<UIBase*> uiBases = mUIBases;
		while (!uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();
			if (uiBase)
			{
				uiBase->Render(InHdc);
				uiBases.pop();
			}
		}
	}
	void UIManager::Push(enums::EUIType InType)
	{
		mRequestUIQueue.push(InType);
	}
	void UIManager::Pop(enums::EUIType InType)
	{
		if (mUIBases.empty())
		{
			return;
		}

		std::stack<UIBase*> tempStack;

		UIBase* uiBase = nullptr;
		while (!mUIBases.empty())
		{
			uiBase = mUIBases.top();
			mUIBases.pop();

			if (uiBase->GetType() != InType)
			{
				tempStack.push(uiBase);
				continue;
			}

			if (uiBase->IsFullScreen())
			{
				std::stack<UIBase*> uiInActiveBases = mUIBases;
				while (!uiInActiveBases.empty())
				{
					UIBase* uiInActiveBase = uiInActiveBases.top();
					uiInActiveBases.pop();
					if (uiInActiveBase)
					{
						uiInActiveBase->Active();
					}
				}
			}
			uiBase->UIClear();
			break;
		}

		while (!tempStack.empty())
		{
			uiBase = tempStack.top();
			tempStack.pop();
			uiBase->Active();
			mUIBases.push(uiBase);
		}
	}
	void UIManager::Release()
	{
		for (auto iter : mUIs)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
}
