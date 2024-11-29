#pragma once
#include "CommonInclude.h"
#include "acEntity.h"
#include "acLayer.h"

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

		virtual void OnEnter();
		virtual void OnExit();

		__forceinline Layer* GetLayer(const enums::ELayerType type) { return mLayers[(UINT)type]; }

	private:
		void createLayers();

	private:
		std::vector<Layer*> mLayers;
	};
}
