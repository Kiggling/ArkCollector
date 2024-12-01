#pragma once
#include "CommonInclude.h"

namespace ac
{
	class Entity
	{
	public:
		Entity();
		~Entity();

		__forceinline void SetName(const std::wstring& InName) { mName = InName; }
		__forceinline std::wstring GetName() { return mName; }

	private:
		std::wstring mName;
	};
}

