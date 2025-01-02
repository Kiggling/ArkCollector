#pragma once
#include "CommonInclude.h"

namespace ac
{
	enum class EKeyState
	{
		Down,
		Pressed,
		Up,
		None
	};
	enum class EKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P, 
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		UP, DOWN, LEFT, RIGHT,
		LBUTTON, MBUTTON, RBUTTON, SPACEBAR,
		One, Two, Three, Four,
		End
	};

	class Input
	{
	public:
		struct FKey
		{
			EKeyCode keyCode;
			EKeyState keyState;
			bool bIsPressed;
		};

		static void Initialize();
		static void Update();


		__forceinline static bool GetKeyDown(EKeyCode InKeyCode) { return mKeys[(UINT)InKeyCode].keyState == EKeyState::Down; }
		__forceinline static bool GetKeyUp(EKeyCode InKeyCode) { return mKeys[(UINT)InKeyCode].keyState == EKeyState::Up; }
		__forceinline static bool GetKey(EKeyCode InKeyCode) { return mKeys[(UINT)InKeyCode].keyState == EKeyState::Pressed; }
		__forceinline static math::Vector2 GetMousePosition() { return mMousePosition; }
	private:
		static void updateAllKeys();
		static void setPressedState(UINT key);
		static void setNotPressedState(UINT key);
		static void getMousePointPositionByWindow();
		static void clearKeys();
	private:
		static std::vector<FKey> mKeys;
		static math::Vector2 mMousePosition;

	};
}

