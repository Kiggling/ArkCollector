#include "acApplication.h"
#include "acGameObject.h"

namespace ac
{
	Application::Application()
		: mHwnd(nullptr)
		, mHdc(nullptr)
	{

	}
	Application::~Application()
	{

	}

	void Application::Initialize(HWND InHwnd, UINT width, UINT height)
	{
	}
	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}
	void Application::Update()
	{
	}
	void Application::LateUpdate()
	{
		
	}
	void Application::Render()
	{
		
	}
}