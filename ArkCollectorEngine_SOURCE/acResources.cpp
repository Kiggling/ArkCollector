#include "acResources.h"

namespace ac
{
	std::map<std::wstring, Resource*> Resources::mResources = {};
	std::mutex Resources::mMtx;
}