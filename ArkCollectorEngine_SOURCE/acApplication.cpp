#include "CommonInclude.h"
#include "acApplication.h"
#include "acTime.h"
#include "acInput.h"
#include "acSceneManager.h"
#include "acCollisionManager.h"

namespace ac
{
	Application::Application()
		: mHwnd(nullptr)
		, mHdc(nullptr)
		, mBackHdc(nullptr)
		, mBackBitmap(nullptr)
		, mWidth(0)
		, mHeight(0)
	{

	}

	Application::~Application()
	{

	}

	void Application::Initialize(HWND InHwnd, UINT width, UINT height)
	{
		adjustWindowRect(InHwnd, width, height);
		createBuffer(width, height);

		Input::Initialize();
		Time::Initialize();
		SceneManager::Initialize();
		CollisionManager::Initialize();
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();

		Destroy();
	}

	void Application::Update()
	{
		Input::Update();
		Time::Update();
		CollisionManager::Update();
		SceneManager::Update();
	}

	void Application::LateUpdate()
	{
		SceneManager::LateUpdate();
		CollisionManager::LateUpdate();
	}

	void Application::Render()
	{
		// mBackHdc �����
		clearRenderTarget();

		// ȭ�鿡 ����ϰ��� �ϴ� Ŭ������ Render �Լ� ȣ�� (���ڷ� mBackHdc ���)
		SceneManager::Render(mBackHdc);
		CollisionManager::Render(mBackHdc);

		// mBackHdc�� �׸� �͵��� mHdc�� ����
		copyRenderTarget(mBackHdc, mHdc);
	}

	void Application::Destroy()
	{
		SceneManager::Destroy();
	}

	void Application::adjustWindowRect(HWND hwnd, UINT width, UINT height)
	{
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);

		RECT rect = { 0, 0, width, height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;

		SetWindowPos(hwnd, nullptr, 0, 0, mWidth, mHeight, 0);
		ShowWindow(hwnd, true);
	}

	void Application::createBuffer(UINT width, UINT height)
	{
		mBackBitmap = CreateCompatibleBitmap(mHdc, width, height);
		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBitmap);
		DeleteObject(oldBitmap);
	}

	void Application::clearRenderTarget()
	{
		HBRUSH grayBrush = (HBRUSH)CreateSolidBrush(RGB(128, 128, 128));
		HBRUSH oldBrush = (HBRUSH)SelectObject(mBackHdc, grayBrush);

		Rectangle(mBackHdc, -1, -1, mWidth + 1, mHeight + 1);

		(HBRUSH)SelectObject(mBackHdc, oldBrush);
		DeleteObject(grayBrush);
	}

	void Application::copyRenderTarget(HDC source, HDC dest)
	{
		BitBlt(dest, 0, 0, mWidth, mHeight, source, 0, 0, SRCCOPY);
	}
}