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
		LBUTTON, MBUTTON, RBUTTON, 
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

		void Initialize();
		void Update();


		__forceinline static bool GetKeyDown(EKeyCode InKeyCode) { return mKeys[(UINT)InKeyCode].keyState == EKeyState::Down; }
		__forceinline static bool GetKeyUp(EKeyCode InKeyCode) { return mKeys[(UINT)InKeyCode].keyState == EKeyState::Up; }
		__forceinline static bool GetKey(EKeyCode InKeyCode) { return mKeys[(UINT)InKeyCode].keyState == EKeyState::Pressed; }
		__forceinline static math::Vector2 GetMousePosition() { return mMousePosition; }
	private:
		void updateAllKeys();
		void setPressedState(UINT key);
		void setNotPressedState(UINT key);
		void getMousePointPositionByWindow();
		void clearKeys();
	private:
		static std::vector<FKey> mKeys;
		static math::Vector2 mMousePosition;

	};
}

