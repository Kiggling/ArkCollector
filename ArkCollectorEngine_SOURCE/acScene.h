#pragma once
#include "CommonInclude.h"
#include "acEntity.h"
#include "acLayer.h"
#include "acGameObject.h"

namespace ac
{
	class Scene : public Entity
	{
	public:
		Scene();
		~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(GameObject* gameObj, const enums::ELayerType layerType);
		void EraseGameObject(GameObject* gameObj);
		__forceinline Layer* GetLayer(const enums::ELayerType type) { return mLayers[(UINT)type]; }

	private:
		void createLayers();

	private:
		std::vector<Layer*> mLayers;
	};
}
