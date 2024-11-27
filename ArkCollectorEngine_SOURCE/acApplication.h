#pragma once

#include <Windows.h>

namespace ac
{
	class Application
	{
	public:
		Application();
		~Application();

		void Initialize(HWND InHwnd, UINT width, UINT height);
		void Run();
		void Update();
		void LateUpdate();
		void Render();

		__forceinline HWND GetHwnd() const { return mHwnd; }
		__forceinline HDC GetHdc() const { return mHdc; }
		__forceinline UINT GetWidth() const { return mWidth; }
		__forceinline UINT GetHeight() const { return mHeight; }

	private:
		void adjustWindowRect(HWND hwnd, UINT width, UINT height);
		void createBuffer(UINT width, UINT height);
		void clearRenderTarget();
		void copyRenderTarget(HDC source, HDC dest);

	private:
		HWND mHwnd;
		HDC mHdc;

		HDC mBackHdc;
		HBITMAP mBackBitmap;

		UINT mWidth;
		UINT mHeight;
	};
}
