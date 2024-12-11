#pragma once
#include "..\\ArkCollectorEngine_SOURCE\\acSceneManager.h"

#include "acTestScene.h"
#include "acToolScene.h"

namespace ac
{
	void LoadScenes()
	{
		//SceneManager::CreateScene<>();
		/*SceneManager::CreateScene<TestScene>(L"TestScene");
		SceneManager::LoadScene(L"TestScene");*/

		SceneManager::CreateScene<ToolScene>(L"ToolScene");
		SceneManager::CreateScene<TestScene>(L"TestScene");
		SceneManager::LoadScene(L"ToolScene");
	}
}
