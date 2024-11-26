#include "acInput.h"
#include "acApplication.h"

extern ac::Application application;

namespace ac
{
	std::vector<Input::FKey> Input::mKeys = {};
	int ASCII[(UINT)EKeyCode::End] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT,
		VK_LBUTTON, VK_MBUTTON, VK_RIGHT,
	};

	void Input::Initialize()
	{
		for (size_t i = 0; i < (UINT)EKeyCode::End; i++)
		{
			FKey key;
			key.keyCode = (EKeyCode)i;
			key.keyState = EKeyState::None;
			key.bIsPressed = false;

			mKeys.push_back(key);
		}
	}
	void Input::Update()
	{
		if (GetFocus())
		{
			updateAllKeys();
			getMousePointPositionByWindow();
		}
		else
		{
			clearKeys();
		}
	}




	void Input::updateAllKeys()
	{
		for (size_t i = 0; i < (UINT)EKeyCode::End; i++)
		{
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				setPressedState(i);
			}
			else
			{
				setNotPressedState(i);
			}
		}
	}
	void Input::setPressedState(UINT key)
	{
		if (mKeys[key].bIsPressed)
		{
			mKeys[key].keyState = EKeyState::Pressed;
		}
		else
		{
			mKeys[key].keyState = EKeyState::Down;
		}
		mKeys[key].bIsPressed = true;
	}
	void Input::setNotPressedState(UINT key)
	{
		if (mKeys[key].bIsPressed)
		{
			mKeys[key].keyState = EKeyState::Up;
		}
		else
		{
			mKeys[key].keyState = EKeyState::None;
		}
		mKeys[key].bIsPressed = false;
	}
	void Input::getMousePointPositionByWindow()
	{
		//POINT mousePos = {};
		//GetCursorPos(&mousePos);
		//ScreenToClient(application.GetHwnd(), &mousePos);

		//UINT width = application.GetWidth();
		//UINT height = application.GetHeight();

		//mMousePosition.x = -1.f;
		//mMousePosition.y = -1.f;

		//if (mousePos.x < width && mousePos.x > 0)
		//{
		//	mMousePosition.x = mousePos.x;
		//}
		//if (mousePos.y < Height && mousePos.y > 0)
		//{
		//	mMousePosition.y = mousePos.y;
		//}
	}
	void Input::clearKeys()
	{
		for (FKey key : mKeys)
		{
			if (key.keyState == EKeyState::Down || key.keyState == EKeyState::Pressed)
			{
				key.keyState = EKeyState::Up;
			}
			else if(key.keyState == EKeyState::Up)
			{
				key.keyState = EKeyState::None;
			}
			key.bIsPressed = false;
		}
	}
}