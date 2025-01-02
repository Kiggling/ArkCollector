#pragma once
#include "acGameObject.h"
#include "acSceneManager.h"
#include "acTransformComponent.h"

namespace ac::object
{
	template <typename T>
	static T* Instantiate(ac::enums::ELayerType layerType)
	{
		T* gameObject = new T();
		gameObject->SetLayerType(layerType);
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(layerType);
		layer->AddGameObject(gameObject);

		return gameObject;
	}

	template <typename T>
	static T* Instantiate(ac::enums::ELayerType layerType, math::Vector2 position)
	{
		T* gameObject = new T();
		gameObject->SetLayerType(layerType);
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(layerType);
		layer->AddGameObject(gameObject);

		TransformComponent* tr = gameObject->GetComponent<TransformComponent>();
		tr->SetPosition(position);

		return gameObject;
	}

	static void DontDestroyOnLoad(GameObject* gameObj)
	{
		Scene* activeScene = SceneManager::GetActiveScene();
		activeScene->EraseGameObject(gameObj);

		Scene* dontDestroyOnLoad = SceneManager::GetDontDestroyOnLoad();
		dontDestroyOnLoad->AddGameObject(gameObj, gameObj->GetLayerType());
	}
}
