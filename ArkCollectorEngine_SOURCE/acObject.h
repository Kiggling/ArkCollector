#pragma once
#include "acGameObject.h"
#include "acTransformComponent.h"
#include "acSceneManager.h"
#include "acScene.h"
#include "acLayer.h"

namespace ac::object
{
	template<typename T>
	static T* Instantiate(ac::enums::ELayerType InType)
	{
		T* gameObject = new T();
		gameObject->SetLayerType(InType);
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(InType);
		layer->AddGameObject(gameObject);

		return gameObject;
	}

	template<typename T>
	static T* Instantiate(ac::enums::ELayerType InType, math::Vector2 InPosition)
	{
		T* gameObject = new T();
		gameObject->SetLayerType(InType);
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(InType);
		layer->AddGameObject(gameObject);

		TransformComponent* tr = gameObject->GetComponent<TransformComponent>();
		tr->SetPosition(InPosition);

		return gameObject;
	}
}
