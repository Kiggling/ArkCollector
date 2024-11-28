#pragma once
#include "CommonInclude.h"
#include "acEntity.h"
#include "acGameObject.h"

namespace ac
{
	class Layer : public Entity
	{
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		void AddGameObject(GameObject* gameObject);
		void EraseGameObject(GameObject* eraseGameObj);
		const std::vector<GameObject*> GetGameObjects() { return mGameObjects; }


	private:
		// 게임오브젝트를 담은 vector
		std::vector<GameObject*> mGameObjects;
	};
}
