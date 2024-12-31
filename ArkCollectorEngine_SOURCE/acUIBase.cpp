#include "acUIBase.h"

namespace ac
{
	UIBase::UIBase(enums::EUIType InType)
		: mType(InType)
		, mbFullScreen(false)
		, mbEnabled(false)
	{
	}
	UIBase::~UIBase()
	{
	}
	void UIBase::Initialize()
	{
		OnInit();
	}
	void UIBase::Active()
	{
		mbEnabled = true;
		OnActive();
	}
	void UIBase::InActive()
	{
		mbEnabled = false;
		OnInActive();
	}
	void UIBase::Update()
	{
		if (mbEnabled)
		{
			OnUpdate();
		}
	}
	void UIBase::LateUpdate()
	{
		if (mbEnabled)
		{
			OnLateUpdate();
		}
	}
	void UIBase::Render(HDC InHdc)
	{
		if (mbEnabled)
		{
			OnRender(InHdc);
		}
	}
	void UIBase::UIClear()
	{
		OnClear();
	}
	void UIBase::OnInit()
	{
	}
	void UIBase::OnActive()
	{
	}
	void UIBase::OnInActive()
	{
	}
	void UIBase::OnUpdate()
	{
	}
	void UIBase::OnLateUpdate()
	{
	}
	void UIBase::OnRender(HDC InHdc)
	{
	}
	void UIBase::OnClear()
	{
	}
}