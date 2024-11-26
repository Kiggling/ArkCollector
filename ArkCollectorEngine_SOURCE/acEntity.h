#pragma once
#include <string>

namespace ac
{
	class Entity
	{
	public:
		Entity();
		~Entity();

		__forceinline void SetName(std::wstring& InName) { mName = InName; }
		__forceinline std::wstring GetName() { return mName; }

	private:
		std::wstring mName;
	};
}

