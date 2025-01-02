#include "acScene.h"

namespace ac
{
	Scene::Scene()
		: mLayers{}
	{
		createLayers();
	}

	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
		for (Layer* layer : mLayers)
		{
			if (layer == nullptr)
				continue;

			layer->Initialize();
		}
	}

	void Scene::Update()
	{
		for (Layer* layer : mLayers)
		{
			if (layer == nullptr)
				continue;

			layer->Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (Layer* layer : mLayers)
		{
			if (layer == nullptr)
				continue;

			layer->LateUpdate();
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (Layer* layer : mLayers)
		{
			if (layer == nullptr)
				continue;

			layer->Render(hdc);
		}
	}

	void Scene::Destroy()
	{
		for (Layer* layer : mLayers)
		{
			if (layer == nullptr)
				continue;

			layer->Destroy();
		}
	}

	void Scene::OnEnter()
	{
	}

	void Scene::OnExit()
	{
	}

	void Scene::AddGameObject(GameObject* gameObj, const enums::ELayerType layerType)
	{
		mLayers[(UINT)layerType]->AddGameObject(gameObj);
	}

	void Scene::EraseGameObject(GameObject* gameObj)
	{
		enums::ELayerType layerType = gameObj->GetLayerType();
		mLayers[(UINT)layerType]->EraseGameObject(gameObj);
	}

	void Scene::createLayers()
	{
		mLayers.resize((UINT)enums::ELayerType::Max);
		for (size_t i = 0; i < (UINT)enums::ELayerType::Max; i++)
		{
			mLayers[i] = new Layer();
		}
	}
}