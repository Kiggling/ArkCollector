#pragma once
#include "acEntity.h"

namespace ac
{
	class Resource abstract : public Entity
	{
	public:
		Resource(enums::EResourceType type);
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;

		const std::wstring& GetPath() { return mPath; }
		void SetPath(const std::wstring& path) { mPath = path; }

	private:
		const enums::EResourceType mType;
		std::wstring mPath;
	};
}
