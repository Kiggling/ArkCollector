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

	private:
		HWND mHwnd;
		HDC mHdc;
	};
}
